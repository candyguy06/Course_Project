module dcache_ctrl(stall, wr_cache, valid_in, wr_mem, rd_mem, sel_tag_mem, sel_data_cache, Rd, Wr, hit, clk, rst, valid, mem_change, req, datahiz, cs, all_line, dirty, dirty_in);

  output wr_cache, valid_in; // for cache
  output wr_mem, rd_mem; // for main memory
  output stall; // for top-level output
  output sel_data_cache;
  output sel_tag_mem;
  output datahiz;
  output cs;
  output all_line;
  output dirty_in;
  input Rd, Wr; // from primary input 
  input hit; // from cache
  input clk, rst, valid;
  input mem_change;
  input req;
  input dirty;

  reg [3:0] cs;
  reg [3:0] ns;
  parameter IDLE = 4'd0, READ = 4'd1, RDMISS = 4'd2, RDMEM = 4'd3, RDDATA = 4'd4, WRITE = 4'd5, WRHIT = 4'd6, WRMISS = 4'd7, WRMEM = 4'd8 ,  RDHIT = 4'd9 , WB = 4'd10, WRDATA = 4'd11, WBpre = 4'd12;
  //state reg
  //WRDATA從cache讀data
always@(posedge clk or rst )
begin
  if(rst)
    cs <= IDLE;
  else
    cs <= ns;
end
  
//next state logic
always@(*)
begin
  case(cs)
    IDLE:begin
        if(~rst)
          begin
            if(Rd & !Wr)
              ns = READ;
            else if(!Rd & Wr)
              ns = WRITE;
            else
              ns = IDLE;
          end
        else
          ns = IDLE;
        end//IDLE
    READ:begin
      if( valid && hit )
        ns = RDHIT;
      else
        ns = RDMISS;
    end//READ
    RDHIT:begin
      ns = RDDATA;
    end
    RDMISS:begin
      ns = RDMEM;
    end
    WBpre:begin
      ns = WB;
    end
    WB:begin
      ns = RDMEM;
    end
    RDMEM:
      ns = (mem_change) ? RDDATA : RDMEM ;
    RDDATA:begin
        if(~rst)
          begin
            if(Rd & !Wr)
              ns = READ;
            else if(!Rd & Wr)
              ns = WRITE;
            else 
              ns = IDLE;
          end
        else
          ns = IDLE;
        end//rddata
    WRITE:
      if( valid && hit )
        ns = WRHIT;
      else
        ns = WRMISS;
    WRHIT:
      ns = WRMEM;
    WRDATA:begin//cpu從cache讀資料
        if(~rst)
          begin
            if(Rd & !Wr)
              ns = READ;
            else if(!Rd & Wr)
              ns = WRITE;
            else 
              ns = IDLE;
          end
        else
          ns = IDLE;
        end
    WRMISS:
    ns = WRMEM;
    WRMEM:begin
        if(~rst)
          begin
            if(Rd & !Wr)
              ns = READ;
            else if(!Rd & Wr)
              ns = WRITE;
            else
              ns = IDLE;
          end
        else
          ns = IDLE;
        end//wrmem
    default:
    ns = IDLE;
  endcase
end

//output logic

//cache是否寫入data(可能從cpu或memory)
assign wr_cache       = (cs == RDMEM) | (cs == WRHIT) | (cs == WRMISS) ;

//cache是否寫入valid
assign valid_in       = (cs == RDMEM) | (cs == WRHIT) | (cs == WRMISS) ;

//cache是否寫入dirty
assign dirty_in       = 0 ;

//memory是否寫入data
assign wr_mem         = (cs == WRMEM) | (cs == WB);

//是否讀取memory
assign rd_mem         = (cs == RDMISS) ;

// 決定進入cache的資料從哪來 1 - 從記憶體, 0 - 從CPU
assign sel_data_cache = (cs == IDLE) | (cs == READ) | (cs == RDHIT) | (cs == RDMISS) | (cs == RDMEM) | (cs == WB) | (cs == RDDATA) ;

//決定送去memory讀取資料的address中 , tag 要從哪來 1 - 從cache(發生在 Write back情形), 0 - 從CPU
assign sel_tag_mem    = (cs == IDLE) | (cs == WB) | (cs == WRDATA) ;

//決定CPU是否stall
assign stall          = (cs == READ) | (cs == RDHIT) | (cs == RDMISS) | (cs == RDMEM) | (cs == WB) |  (cs == WRITE) | (cs == WRHIT) | (cs == WRMISS) | (cs == WBpre);

//決定data out 是否為HiZ
assign datahiz        = (cs == IDLE) ;

//決定何時要一次寫入cache的所有line
assign all_line       = (cs == RDMEM) ;





  
endmodule
