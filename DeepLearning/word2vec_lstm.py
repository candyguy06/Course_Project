import time
import numpy as np
import tensorflow as tf
import reader as reader

tf.logging.set_verbosity(tf.logging.ERROR)

config = tf.ConfigProto()
config.gpu_options.allow_growth = True
session = tf.Session(config=config)

class PTBInput(object):
  '''
  The input data.
  config中有batch_size.num_steps
  num_steps:LSTM的展開步數(unrolled steps of LSTM)
  epoch_size:每个epoch內需要多少次訓練的疊代
  '''
  def __init__(self, config, data, name=None):
    self.batch_size = batch_size = config.batch_size
    self.num_steps = num_steps = config.num_steps

    self.epoch_size = ((len(data) // batch_size) - 1) // num_steps
    self.input_data, self.targets = reader.ptb_producer(data, batch_size,
                                                    num_steps, name=name)

class PTBModel(object):
  '''
  The PTB model 語言模型
  input_: batch_size和num_steps
  config: hidden_size(LSTM節點數)和vocab_size(詞彙表大小)
  '''
  def __init__(self, is_training, config, input_):
    self._input = input_

    batch_size = input_.batch_size
    num_steps = input_.num_steps
    size = config.hidden_size
    vocab_size = config.vocab_size
    
    def lstm_cell():
      return tf.nn.rnn_cell.LSTMCell(size, forget_bias=0.0, 
                              state_is_tuple=True, 
                              name='basic_lstm_cell')
    
    attn_cell = lstm_cell

    if is_training and config.keep_prob < 1:
      def attn_cell():
        return tf.nn.rnn_cell.DropoutWrapper(lstm_cell(), 
                                    output_keep_prob=config.keep_prob)

    cell = tf.nn.rnn_cell.MultiRNNCell([attn_cell() for _ in range(config.num_layers)], state_is_tuple=True)
    self._initial_state = cell.zero_state(batch_size, tf.float32)

    # 指定在cpu上執行
    # 將單詞的ID轉換為向量，embedding的維度VOCAB_SIZE * SIZE.
    with tf.device("/cpu:0"):
      embedding = tf.get_variable("embedding", [vocab_size, size], 
                                                dtype=tf.float32)
      inputs = tf.nn.embedding_lookup(embedding, input_.input_data)

    if is_training and config.keep_prob < 1:
      inputs = tf.nn.dropout(inputs, config.keep_prob)

    outputs = []
    state = self._initial_state
    with tf.variable_scope("RNN"):
      # 控制訓練
      for time_step in range(num_steps):
        if time_step > 0 :
          tf.get_variable_scope().reuse_variables()  

        (cell_output, state) = cell(inputs[:, time_step, :], state)
        outputs.append(cell_output)

    # flatten
    output = tf.reshape(tf.concat(outputs, 1), [-1, size])
    # 定義softmax層
    # 从size的向量轉換為vocab_size的ID
    softmax_w = tf.get_variable("softmax_w", 
                                [size, vocab_size], 
                                dtype=tf.float32)
    softmax_b = tf.get_variable("softmax_b", 
                                [vocab_size], 
                                dtype=tf.float32)

    logits = tf.matmul(output, softmax_w) + softmax_b
    # 計算loss
    loss = tf.contrib.legacy_seq2seq.sequence_loss_by_example([logits], 
                [tf.reshape(input_.targets, [-1])], 
                [tf.ones([batch_size * num_steps], 
                dtype=tf.float32)])
    # 計算得到每个batch的損失
    self._cost = cost = tf.reduce_sum(loss) / batch_size
    self._final_state = state

    # 訓練的时候定義反向傳播操作，不是訓練狀態就返回
    if not is_training:
      return

    # 定義learning rate
    self._lr = tf.Variable(0.0, trainable=False)
    # 獲取所有可訓練的参數tvars,針對前面得到的cost,計算tvars梯度
    # 並tf.clip_by_global_norm設置梯度的最大範圍,程度上起到了正規化的作用
    # 這就是Gradient Clipping的方法,控制梯度的最大範圍,防止Gradient Explosion梯度爆炸
    tvars = tf.trainable_variables()
    grads, _ = tf.clip_by_global_norm(tf.gradients(cost, tvars), 
                                      config.max_grad_norm)
                                      
    optimizer = tf.train.GradientDescentOptimizer(self._lr)
    # 用optimizer.apply_gradients將前面clip過的梯度應用到所有可訓練的参数tvars上
    # 然後使用tf.contrib.framework.get_or_create_global_step()生成统一的訓練步數
    self._train_op = optimizer.apply_gradients(zip(grads, tvars), 
                    global_step=tf.train.get_or_create_global_step())

    # 創建_new_lr控制learning rate
    self._new_lr = tf.placeholder(tf.float32, shape=[], 
                               name="new_learning_rate")
    self._lr_update = tf.assign(self._lr, self._new_lr)

  # assign_lr用於外部控制模型的學習速率
  def assign_lr(self, session, lr_value):
    session.run(self._lr_update, feed_dict={self._new_lr: lr_value})

  # 定義PTBModel class的一些property

  @property
  def input(self):
    return self._input

  @property
  def initial_state(self):
    return self._initial_state

  @property
  def cost(self):
    return self._cost

  @property
  def final_state(self):
    return self._final_state

  @property
  def lr(self):
    return self._lr

  @property
  def train_op(self):
    return self._train_op
    
  '''
    定義不同大小的模型的參數
    init_scale  初始權重值
    learning_rate 學習率的初始值
    max_grad_norm 梯度的最大範圍
    num_layers LSTM堆叠的層數
    num_steps  LSTM梯度反向傳播展开步數
    hidden_size  LSTM内含節點數
    max_epoch  初始學習率可訓練的epoch
    max_max_epoch  總共可訓練的epoch
    keep_prob  dropout比率
    lr_decay  學習率衰減速度
    batch_size  batch中樣本數量
    vocab_size  
  '''

class SmallConfig(object):
  """Small config."""
  init_scale = 0.1
  learning_rate = 1.0
  max_grad_norm = 5
  num_layers = 2
  num_steps = 20
  hidden_size = 200
  max_epoch = 8
  max_max_epoch = 13
  keep_prob = 1.0 
  lr_decay = 0.5
  batch_size = 20
  vocab_size = 10000

class MediumConfig(object):
  init_scale = 0.05
  learning_rate = 1.0
  max_grad_norm = 5
  num_layers = 5
  num_steps = 35
  hidden_size = 650
  max_epoch = 12
  max_max_epoch = 39
  keep_prob = 0.5
  lr_decay = 0.8
  batch_size = 20
  vocab_size = 10000

class LargeConfig(object):
  init_scale = 0.04
  learning_rate = 1.0
  max_grad_norm = 10
  num_layers = 5
  num_steps = 35
  hidden_size = 1500
  max_epoch = 20
  max_max_epoch = 55
  keep_prob = 0.35
  lr_decay = 1 / 1.15
  batch_size = 20
  vocab_size = 10000


class TestConfig(object):
  """Tiny config, for testing."""
  init_scale = 0.1
  learning_rate = 1.0
  max_grad_norm = 1
  num_layers = 1
  num_steps = 2
  hidden_size = 2
  max_epoch = 1
  max_max_epoch = 1
  keep_prob = 1.0
  lr_decay = 0.5
  batch_size = 20
  vocab_size = 10000

def run_epoch(session, model, eval_op=None, verbose=False):
  """Runs the model on the given data."""
  start_time = time.time()
  costs = 0.0
  iters = 0
  state = session.run(model.initial_state)

  fetches = {
      "cost": model.cost,
      "final_state": model.final_state
  }

  if eval_op is not None:
    fetches["eval_op"] = eval_op

  for step in range(model.input.epoch_size):
    feed_dict = {}
    # 使用當前資料訓練或預測模型
    for i, (c, h) in enumerate(model.initial_state): # 將全部的狀態加入
      feed_dict[c] = state[i].c
      feed_dict[h] = state[i].h

    vals = session.run(fetches, feed_dict) # 訓練
    cost = vals["cost"]
    state = vals["final_state"]

    costs += cost
    iters += model.input.num_steps

    if verbose and step % (model.input.epoch_size // 10) == 10:
      print("%.3f perplexity: %.3f speed: %.0f wps" %
           (step * 1.0 / model.input.epoch_size, np.exp(costs / iters),
            iters * model.input.batch_size / (time.time() - start_time)))

  return np.exp(costs / iters)

raw_data = reader.ptb_raw_data('simple-examples/data/')
train_data, valid_data, test_data, _ = raw_data

config = SmallConfig()
eval_config = SmallConfig()
eval_config.batch_size = 1
eval_config.num_steps = 1

with tf.Graph().as_default():
  initializer = tf.random_uniform_initializer(-config.init_scale, 
                                        config.init_scale)

  with tf.name_scope("Train"):
    train_input = PTBInput(config=config, data=train_data,
                            name="TrainInput")
    with tf.variable_scope("Model", reuse=None, initializer=initializer):
      m = PTBModel(is_training=True, config=config, input_=train_input)
      #tf.scalar_summary("Training Loss", m.cost)
      #tf.scalar_summary("Learning Rate", m.lr)

  with tf.name_scope("Valid"):
    valid_input = PTBInput(config=config, data=valid_data, 
                            name="ValidInput")
    with tf.variable_scope("Model", reuse=True, initializer=initializer):
      mvalid = PTBModel(is_training=False, config=config, 
                          input_=valid_input)
      #tf.scalar_summary("Validation Loss", mvalid.cost)

  with tf.name_scope("Test"):
    test_input = PTBInput(config=eval_config, data=test_data, 
                            name="TestInput")
    with tf.variable_scope("Model", reuse=True, initializer=initializer):
      mtest = PTBModel(is_training=False, config=eval_config, 
                        input_=test_input)

  merged = tf.summary.merge_all()                    
 
  # 創建訓練的管理器
  sv = tf.train.Supervisor(logdir='tmp')
  with sv.managed_session() as session:
    for i in range(config.max_max_epoch):
      lr_decay = config.lr_decay ** max(i + 1 - config.max_epoch, 0.0)
      m.assign_lr(session, config.learning_rate * lr_decay)

      print("Epoch: %d Learning rate: %.3f" % (i + 1, session.run(m.lr)))
      train_perplexity = run_epoch(session, m, eval_op=m.train_op, verbose=True)
      print("Epoch: %d Train Perplexity: %.3f" % (i + 1, train_perplexity))
      valid_perplexity = run_epoch(session, mvalid)
      print("Epoch: %d Valid Perplexity: %.3f" % (i + 1, valid_perplexity))

      result = session.run(merged)
      sv.summary_computed(session, result, global_step=i)
      
    test_perplexity = run_epoch(session, mtest)
    print("Test Perplexity: %.3f" % test_perplexity)
    
    #print("Saving model to %s." % FLAGS.save_path)
    #sv.saver.save(session, FLAGS.save_path, global_step=sv.global_step)
    

