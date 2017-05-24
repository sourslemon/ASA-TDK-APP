使用方式

Step1. 下載整個專案，或使用git clone

Step2.
開啟專案資料夾，並在Test資料夾中，新增愈編譯之.c檔

Step3.
引用函式庫。
ASA_Lib.h為ASA標準函示庫。
TDK_LIB.h為TDK函式庫，源碼皆放在TDK_Lib中。
``` c
#include "..\TDK_Lib\ASA_Lib.h"
#include "..\TDK_Lib\TDK_LIB.h"
```

Step4.
撰寫程式並編譯檔案

1. 開啟命令提示字元 -> 更改工作目錄到專案目錄底下
EX: 專案目錄為 D:\ASA-TDK-APP
輸入 `D:` 切換到D槽   
 輸入 `cd ASA-TDK-APP` 切換到 D:\ASA-TDK-APP  

2. 輸入 `make {愈編譯之檔案名稱}.a` 即可自動編譯  
 並會將編譯好之hex檔放在hex資料夾中  
 EX: `make test_motor_steps_by_timer2.a`

Step5.
將編譯好之hex燒入進m128並測試
