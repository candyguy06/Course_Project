setwd("C:/Users/ben/Desktop/R/智慧技術/pj1/")
X = as.data.frame(read.csv("supermarket_sales - Sheet1.csv"))
head(X,5); dim(X)
#   Invoice.ID      Branch  City    Customer.type Gender    Product.line        Unit.price  Quantity  Tax.5.
# 1 750-67-8428      A    Yangon        Member Female      Health and beauty      74.69        7    26.1415
# 2 226-31-3081      C Naypyitaw        Normal Female Electronic accessories      15.28        5    3.8200
# 3 631-41-3108      A    Yangon        Normal   Male     Home and lifestyle      46.33        7    16.2155
# 4 123-19-1176      A    Yangon        Member   Male      Health and beauty      58.22        8    23.2880
# 5 373-73-7910      A    Yangon        Normal   Male      Sports and travel      86.31        7    30.2085
#   Total      Date   Time      Payment   cogs  gross.margin.percentage gross.income Rating
# 1 548.9715  1/5/2019 13:08     Ewallet 522.83                4.761905      26.1415    9.1
# 2  80.2200  3/8/2019 10:29        Cash  76.40                4.761905       3.8200    9.6
# 3 340.5255  3/3/2019 13:23 Credit card 324.31                4.761905      16.2155    7.4
# 4 489.0480 1/27/2019 20:33     Ewallet 465.76                4.761905      23.2880    8.4
# 5 634.3785  2/8/2019 10:37     Ewallet 604.17                4.761905      30.2085    5.3
# [1] 1000   17

names(X)
# [1] "Invoice.ID"              "Branch"                  "City"                    "Customer.type"          
# [5] "Gender"                  "Product.line"            "Unit.price"              "Quantity"               
# [9] "Tax.5."                  "Total"                   "Date"                    "Time"                   
# [13] "Payment"                 "cogs"                    "gross.margin.percentage" "gross.income"           
# [17] "Rating" 
X$Date = as.Date(X$Date,format="%m/%d/%Y")  #-- as.--() 是萬用數據轉換函式，此處是將字串型態 轉為 日期型態
# 格式轉換
X$hour =as.integer(substr(X$Time,1,2))  

length(unique(X$City)) ;unique(X$City)
# [1] 3
# [1] "Yangon"    "Naypyitaw" "Mandalay" 
length(unique(X$Branch)) ;unique(X$Branch)
# [1] 3
# [1] "A" "C" "B"
length(unique(X$Customer.type));unique(X$Customer.type)
# [1] 2
# [1] "Member" "Normal"
length(unique(X$Product.line));unique(X$Product.line)
# [1] 6
# [1] "Health and beauty"      "Electronic accessories" "Home and lifestyle"     "Sports and travel"     
# [5] "Food and beverages"     "Fashion accessories"
range(X$Date) 
# [1] "2019-01-01" "2019-03-30"
range(X$Quantity) 
# [1]  1 10
range(X$Unit.price)
# [1] 10.08 99.96

table(X$Quantity)
#   1   2   3   4   5   6   7   8   9  10 
# 112  91  90 109 102  98 102  85  92 119 


X$hour0 = cut( X$hour, breaks = c(9,11,13,17,22))
levels(X$hour0) = c("早上","中午","下午","晚上")
head(X$hour0,5)
# [1] 中午 早上 中午 晚上 早上
# Levels: 早上 中午 下午 晚上

addmargins(table(X$hour0,X$Gender))
#       Female Male  Sum
# 早上    109   82  191
# 中午    107   85  192
# 下午    155  181  336
# 晚上    130  151  281
# Sum     501  499 1000

addmargins(table(X$hour,X$Gender))
#hour  Female Male  Sum
# 10      62   39  101
# 11      47   43   90
# 12      46   43   89
# 13      61   42  103
# 14      39   44   83
# 15      42   60  102
# 16      36   41   77
# 17      38   36   74
# 18      45   48   93
# 19      54   59  113
# 20      31   44   75
# Sum    501  499 1000

sort(X$Unit.price)
length(unique(X$Invoice.ID))

X$pricestage = cut( X$Unit.price, breaks = c(-0.001,40,70,100))
levels(X$pricestage) = c("低價","中價","高價")
head(X$pricestage,5)
# [1] 高價 低價 中價 中價 高價
# Levels: 低價 中價 高價

X$pricestage = cut( X$Unit.price, breaks = c(10,20,30,40,50,60,70,80,90,100))
levels(X$pricestage) = c("10+","20+","30+","40+","50+","60+","70+","80+","90+")
head(X$pricestage,5)
#Levels: 10+ 20+ 30+ 40+ 50+ 60+ 70+ 80+ 90+
    
addmargins(table(X$Product.line,X$pricestage))
#                         低價 中價 高價  Sum
# Electronic accessories   63   34   73  170
# Fashion accessories      55   42   81  178
# Food and beverages       55   45   74  174
# Health and beauty        51   32   69  152
# Home and lifestyle       55   31   74  160
# Sports and travel        53   31   82  166
# Sum                     332  215  453 1000

addmargins(table(X$Product.line,X$pricestage))
#                         10+  20+  30+  40+  50+  60+  70+  80+  90+  Sum
# Electronic accessories   17   30   16   18   16   14   24   17   18  170
# Fashion accessories      19   15   21   20   22   17   18   17   29  178
# Food and beverages       16   21   18   22   23   12   21   19   22  174
# Health and beauty        21   15   15   11   21   20   17   17   15  152
# Home and lifestyle       17   16   22   17   14   18   20   18   18  160
# Sports and travel        16   21   16   19   12   20   20   17   25  166
# Sum                     106  118  108  107  108  101  120  105  127 1000


TT = table(X$Product.line);  TT[order(TT,decreasing=T)][1:6] 
round( 100*sort(table(X$Product.line),decreasing=T)[1:6]/dim(X)[1], 2 )
# Fashion accessories     Food and beverages Electronic accessories      Sports and travel 
# 178                    174                    170                    166 
# 17.8                   17.4                   17.0                   16.6 
# Home and lifestyle      Health and beauty 
# 160                    152 
# 16.0                   15.2 

TT = table(X$Branch,X$Product.line);  addmargins(TT[order(rowSums(TT),decreasing=T), order(colSums(TT),decreasing=T)][,1:6])
#     Fashion accessories Food and beverages Electronic accessories Sports and travel Home and lifestyle
# A                    51                 58                     60                59                 65
# B                    62                 50                     55                62                 50
# C                    65                 66                     55                45                 45
# Sum                 178                174                    170               166                160
# 
#     Health and beauty  Sum
# A                  47  340
# B                  53  332
# C                  52  328
# Sum               152 1000
by(X[,16], X$Branch, sum)
# X$Branch: A
# [1] 5057.16
# --------------------------------------------------------------------------------- 
#   X$Branch: B
# [1] 5057.032
# --------------------------------------------------------------------------------- 
#   X$Branch: C
# [1] 5265.176
by(X[,16], X$Gender, sum)
# X$Gender: Female
# [1] 7994.425
# --------------------------------------------------------------------------------- 
#   X$Gender: Male
# [1] 7384.944
sort(by(X[,16], X$Product.line, sum),decreasing = T)
# X$Product.line
# Food and beverages      Sports and travel Electronic accessories    Fashion accessories 
# 2673.564               2624.896               2587.501               2585.995 
# Home and lifestyle      Health and beauty 
# 2564.853               2342.559

XX = X[,c("Gender","Product.line","hour0")]
require(arules) # apriori關聯式法則的套件
rule <- apriori(XX, 
                # min support & confidence, 最小規則長度(lhs+rhs)
                parameter=list(minlen=3, supp=0.03, conf=0.05),  
                appearance = list(default="lhs",
                                  rhs=c("Gender=Male", "Gender=Female") 
                                  # 右手邊顯示的特徵
                )
)  
inspect(rule)
# lhs                                                 rhs             support confidence coverage
# [1] {Product.line=Health and beauty,hour0=下午}      => {Gender=Male}   0.033   0.6346154  0.052   
# [2] {Product.line=Home and lifestyle,hour0=下午}     => {Gender=Female} 0.030   0.5660377  0.053   
# [3] {Product.line=Sports and travel,hour0=下午}      => {Gender=Male}   0.034   0.5312500  0.064   
# [4] {Product.line=Sports and travel,hour0=下午}      => {Gender=Female} 0.030   0.4687500  0.064   
# [5] {Product.line=Electronic accessories,hour0=下午} => {Gender=Male}   0.033   0.6111111  0.054   
# [6] {Product.line=Food and beverages,hour0=晚上}     => {Gender=Male}   0.031   0.4920635  0.063   
# [7] {Product.line=Food and beverages,hour0=晚上}     => {Gender=Female} 0.032   0.5079365  0.063   
# [8] {Product.line=Food and beverages,hour0=下午}     => {Gender=Male}   0.030   0.5454545  0.055   
# [9] {Product.line=Fashion accessories,hour0=下午}    => {Gender=Female} 0.030   0.5172414  0.058   
# lift      count
# [1] 1.2717743 33   
# [2] 1.1298158 30   
# [3] 1.0646293 34   
# [4] 0.9356287 30   
# [5] 1.2246716 33   
# [6] 0.9860992 31   
# [7] 1.0138453 32   
# [8] 1.0930953 30   
# [9] 1.0324179 30   
sort.rule <- sort(rule, by="lift")
inspect(sort.rule)
# lhs                                                 rhs             support confidence coverage
# [1] {Product.line=Health and beauty,hour0=下午}      => {Gender=Male}   0.033   0.6346154  0.052   
# [2] {Product.line=Electronic accessories,hour0=下午} => {Gender=Male}   0.033   0.6111111  0.054   
# [3] {Product.line=Home and lifestyle,hour0=下午}     => {Gender=Female} 0.030   0.5660377  0.053   
# [4] {Product.line=Food and beverages,hour0=下午}     => {Gender=Male}   0.030   0.5454545  0.055   
# [5] {Product.line=Sports and travel,hour0=下午}      => {Gender=Male}   0.034   0.5312500  0.064   
# [6] {Product.line=Fashion accessories,hour0=下午}    => {Gender=Female} 0.030   0.5172414  0.058   
# [7] {Product.line=Food and beverages,hour0=晚上}     => {Gender=Female} 0.032   0.5079365  0.063   
# [8] {Product.line=Food and beverages,hour0=晚上}     => {Gender=Male}   0.031   0.4920635  0.063   
# [9] {Product.line=Sports and travel,hour0=下午}      => {Gender=Female} 0.030   0.4687500  0.064   
# lift      count
# [1] 1.2717743 33   
# [2] 1.2246716 33   
# [3] 1.1298158 30   
# [4] 1.0930953 30   
# [5] 1.0646293 34   
# [6] 1.0324179 30   
# [7] 1.0138453 32   
# [8] 0.9860992 31   
# [9] 0.9356287 30  

XX = X[,c("Gender","Product.line","hour")]
require(rpart)
set.seed(22)
train.index <- sample(x=1:nrow(XX), size=ceiling(0.8*nrow(XX) ))
train <- XX[train.index, ]
test <- XX[-train.index, ]
cart.model<- rpart(Gender ~. ,                    data=train)
require(rpart.plot) 
prp(cart.model,         # 模型
    faclen=0,           # 呈現的變數不要縮寫
    fallen.leaves=TRUE, # 讓樹枝以垂直方式呈現
    shadow.col="gray",  # 最下面的節點塗上陰影
    # number of correct classifications / number of observations in that node
    extra=2)  

library(jiebaR);         library(stringr);   library(text2vec);   library(data.table)
setDT(X,key="Product.line")
Cv = X[, .(D0=min(Date), Df=max(Date), 
            DD=length(unique(Date)), Tcount=sum(Total), 
            QCount=sum(Quantity)), by=Product.line]
Cv
#           Product.line         D0         Df    DD  Tcount    QCount
# 1: Electronic accessories 2019-01-01 2019-03-30 75 54337.53    971
# 2:    Fashion accessories 2019-01-01 2019-03-30 77 54305.89    902
# 3:     Food and beverages 2019-01-01 2019-03-30 76 56144.84    952
# 4:      Health and beauty 2019-01-01 2019-03-30 73 49193.74    854
# 5:     Home and lifestyle 2019-01-01 2019-03-30 75 53861.91    911
# 6:      Sports and travel 2019-01-01 2019-03-30 78 55122.83    920


#write.csv(X,"Sales.csv")
