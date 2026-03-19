# CamoMouse-Forge

這是一個專注於 USB HID 協定底層通訊的研究專案。旨在透過開發板完整模擬滑鼠的硬體行為與私有描述符，並探討如何透過網路協定進行外部資料流的融合與遠端控制。

過程中希望可以理解滑鼠的運作/通訊原理，並參考其他專案怎麼搭配這些 HID，刻出滑鼠的硬體行為。


## 參考資料

* 所使用的滑鼠: Logitech G402
* 所使用的開發版: CH32V307VCT6
* 參考專案 & 資料:
    * https://github.com/libratbag/libratbag/tree/master
    * https://github.com/openwch/ch32v307/tree/main
    * https://www.cnblogs.com/yangfengwu/p/16143635.html
    

CH32V307VCT6 有提供 USB HID 裝置的範例程式，可以參考 https://github.com/openwch/ch32v307/tree/main/EVT/EXAM/USB/USBFS/DEVICE/CompositeKM

因此會以這個專案為基礎，進行改造



## 專案目標

1. 透過 USB HID 協定底層通訊的研究
2. 理解滑鼠的運作/通訊原理(Current)。
3. 參考其他專案怎麼搭配這些 HID，刻出滑鼠的硬體行為。
4. 探討如何透過網路協定進行外部資料流的融合與遠端控制。


## WireShark 擷取 USB HID 封包

使用 WireShark 的 USBPcap 進行擷取，同時可以搭配 USBTreeViewer 做分析

### 初次擷取封包 (沒有拔出滑鼠)

![alt text](Image/Wireshark/1.png)
<p align="center">圖 1：第一次與 host 交互，可以看到基本的 USB 裝置資訊 VID/PID 等等的</p>

---

![alt text](Image/Wireshark/2.png)
<p align="center">圖 2：第二次與 host 交互，可以看到有兩組 Descriptor</p>


結構上是:
* `Configuration Descriptor`
* `Interface Descriptor` -> `HID Descriptor` -> `Endpoint Descriptor`
* `Interface Descriptor` -> `HID Descriptor` -> `Endpoint Descriptor`

有兩組是因為現在很多滑鼠有提供額外的按鈕，所以會需要兩組 HID 來提供功能(複合型的滑鼠)，用 USBTreeViewer 可以更直觀

![alt text](Image/USBTreeViewer/1.png)

### 發現到的問題

觀察 (圖二) 封包的內容會發現兩個東西

```
USB URB
CONFIGURATION DESCRIPTOR
INTERFACE DESCRIPTOR (0.0): class HID
HID DESCRIPTOR
    bLength: 9
    bDescriptorType: 0x21 (HID)
    bcdHID: 0x0111
    bCountryCode: Not Supported (0x00)
    bNumDescriptors: 1
    bDescriptorType: HID Report (0x22)
    wDescriptorLength: 67 <---
ENDPOINT DESCRIPTOR
INTERFACE DESCRIPTOR (1.0): class HID
HID DESCRIPTOR
    bLength: 9
    bDescriptorType: 0x21 (HID)
    bcdHID: 0x0111
    bCountryCode: Not Supported (0x00)
    bNumDescriptors: 1
    bDescriptorType: HID Report (0x22)
    wDescriptorLength: 151 <---
ENDPOINT DESCRIPTOR
```

有某兩個東西是長度為 67 以及長度 151 的資料，但是 WireShark 後續也沒有看到任何相關的資料，只有滑鼠移動點擊與 host 交互的流程

那 USBTreeViewer 看到的呢?

![alt text](Image/USBTreeViewer/2.png)

AI 給的解釋: 
```
這不是 USBTreeView 這個軟體的 Bug，而是 Windows 作業系統的安全機制與架構限制。

當你把滑鼠或鍵盤插入 Windows 電腦，並完成初始化 (Enumeration) 後，Windows 底層的系統驅動 (hidusb.sys) 會為了防範惡意軟體（例如 User-Space 的 Keylogger 或輸入竄改程式）而獨占 (Exclusive Lock) 這些高權限的 HID 設備。

USBTreeView 是一個運行在應用層 (User-Mode) 的普通軟體。當它試圖透過標準的 Win32 USB API，去向一隻「已經被 Windows 內核鎖死」的滑鼠要那 67 Bytes 和 151 Bytes 的 Report Descriptor 時，Windows 內核會直接拒絕這個請求，並拋出這個籠統的錯誤碼 ERROR_GEN_FAILURE。
```

解決方法: 在滑鼠插入 USB 孔前，WireShark 就要開好

### 再次擷取封包(先拔出滑鼠)

![alt text](Image/Wireshark/3.png)
<p align="center">圖 3：這次可以看到給的資訊更多了，其中出現了兩個大一點的封包(Descriptor Response)。備註: 最上方的深藍色是 ignore 掉的其他裝置</p>

NO.15 ~ NO.36 是原本沒有出現的資料

* NO.15 ~ NO.18 `Unknow type 7f`: 

    ```
    AI: 這個 Unknow type 7f 其實是 Windows 系統特有的一個小動作，它的真實身分是 URB_FUNCTION_GET_MS_FEATURE_DESCRIPTOR。
    它在幹嘛： Windows 系統在滑鼠剛插上去時，會偷偷問滑鼠：「嘿，你有沒有支援微軟的專屬系統描述符 (OS Descriptors)？需不需要我幫你自動上網抓 WinUSB 驅動？」
    ```

* NO.19 ~ NO.26  `Descriptor Request/Response STRING`: 
    ```
    幾乎是一樣的封包，看 Response 是獲取了兩次 "Gaming Mouse G402" 字串
    ```

* NO.27 ~ NO.36  `Descriptor Request/Response HID Report`: 
    ```
    這裡就是重點了，USBTreeViewer 看不到的重要資料
    這裡的資訊將會成為後續改造開發版的重要資料來源
    ```


![alt text](Image/USBTreeViewer/1.png)

HID-compliant mouse:

![alt text](Image/Wireshark/4.png)

HID Keyboard Device + 符合 HID ...

![alt text](Image/Wireshark/5.png)

## 分析 HID 資訊與開發版的程式碼

### 編譯方式

原本編譯 CH32V307VCT6 的程式碼會需要 MRS(MounRiver Studio) 的開發工具
但我希望可以透過自己的 IDE (VSCode or Antigravity) 來開發

Makfile 可以讓 AI 輔助生成，需要讓 AI 理解 MRS(MounRiver Studio) 的環境，MRS 本身就會提供 make.exe，可以從他的專案挖出來用 **(因此還是會依賴 MRS)**

* Firmware: 
    * SRC: `https://github.com/openwch/ch32v307/tree/main/EVT/EXAM/SRC`
    * User: `https://github.com/openwch/ch32v307/tree/main/EVT/EXAM/User`
    * Makefile: 會要求 ToolChain 路徑
        * 例如: `make TOOLCHAIN_PATH="D:/MounRiver/MounRiver_Studio2/resources/app/resources/win32/components/WCH/Toolchain/RISC-V Embedded GCC/bin"`
* make: `D:\MounRiver\MounRiver_Studio2\resources\app\resources\win32\others\Build_Tools\Make\bin\make.exe`

1. 進到 `Firmware`
2. 執行 `D:\MounRiver\MounRiver_Studio2\resources\app\resources\win32\others\Build_Tools\Make\bin\make.exe TOOLCHAIN_PATH="D:/MounRiver/MounRiver_Studio2/resources/app/resources/win32/components/WCH/Toolchain/RISC-V Embedded GCC/bin" USER_DIR="CamoMouse"`
3. 執行成功後，會在 `Firmware/build` 生成很多檔案，其中最重要的就是 `CamoMouse-Forge.hex`
4. https://www.cnblogs.com/yangfengwu/p/16143635.html (這個網站有非常詳細的教學，有三種方式可以燒入 .hex 檔案)
    * 我是用 WCH-LinkE，需要 `D:\MounRiver\MounRiver_Studio2\resources\app\resources\win32\components\WCH\Others\SWDTool\default` 的 `WCH-LinkUtility.exe`

### 重點程式碼分析

* usbd_desc.c
    * HID 資料都在這裡做修改
    * WireShark 擷取的資料得放這裡
    * 其他程式碼也會引用到這裡的資料
    * USBTreeViewer & WireShark dump 出來的資訊放在 HID_info.md
    * 問題是其他資訊也會使用這邊的資料，那依賴於這個檔案的其他程式碼都要改嗎？
        * **長度動態計算 (不需改其他檔案)**：
            * `MyDevDescr`, `MyLangDescr`, `MyManuInfo`, `MyProdInfo`, `MySerNumInfo`, `MyQuaDesc`：被 `usbd_desc.h` 中的巨集讀取陣列第一位元組 `[0]` 自動取得長度。
            * `MyCfgDescr`：被 `usbd_desc.h` 中的巨集讀取陣列的 `[2]` 與 `[3]` 自動取得長度。
        * **寫死長度 (必須手動改 `usbd_desc.h`)**：
            * `KeyRepDesc` 的長度被寫死在 `#define DEF_USBD_REPORT_DESC_LEN_KB`。
            * `MouseRepDesc` 的長度被寫死在 `#define DEF_USBD_REPORT_DESC_LEN_MS`。
            * 如果修改了這兩個 Report 的長度，**務必**去 `usbd_desc.h` 同步更新這兩個巨集！
        * `MyQuaDesc` 在 USBTreeViewer 會看到:

            ![alt text](Image/USBTreeViewer/3.png)
    * ch32v30x_usbfs_device.c 裡面就會使用中斷來獲取這些 desc

* usbd_composite_km.c
    * 滑鼠的行為，但我的開發版沒按鈕，也沒有光學滑鼠的裝置，但實際上只是根據其他腳位的狀態去設定 Data_Pack 傳給 host
    * 主要專注於怎麼發 MS_Data_Pack or KB_Data_Pack 給 host
    * 重點在於:
        * MS_Data_Pack 是 4 bytes，但是 G402 實際是 8 bytes 來控制

            ![alt text](Image/Wireshark/6.png)

            紀錄於: `HID_info.md 的 Mouse Data Pack`
        * KM_Data_Pack 是 8 bytes，但是 G402 實際是 20 bytes 來控制

            ![alt text](Image/Wireshark/7.png)
            
            紀錄於: `HID_info.md 的 Keyboard Data Pack`

        * 會發現 G402 和目前使用的封包有很大的差異
    * 可能會想說，開發版有自己的 HID pack data，和 G402 的 HID pack data，長度、格式，截然不同
      
      那電腦到底是怎麼知道要怎麼操作 ? 
      
      答案就是前面抓到的 HID Report Descriptor 就是操作說明書
    * 這個檔案會被 `g402_pack_builder` 取代掉，因為之後會用其他方式控制滑鼠，`g402_pack_builder` 目前的主要作用就是測試模擬滑鼠移動

* ch32v30x_usbfs_device.c
    * 處理函數中斷
    * 目前只有基本的理解，和處理掉一些不想用到的函數

## 嘗試修改 Descriptor 和使用 G402 的 HID Data

### 初次嘗試失敗 & 成功

這裡的進度
    * 只有改好 Descriptor
    * 把 `usbd_composite_km` 改成 `g402_back_builder`
    * 基本處理 `ch32v30x_usbfs_device.c` 的某些函數(依賴 `usbd_composite_km`)

錯誤分析(下圖可以看到 Malformed Packet):

![alt text](Image/Fail/Failed_1/5.png)

* usbd_desc.c 的基本設定錯誤
    ![alt text](Image/Fail/Failed_1/1.png)

    ![alt text](Image/Fail/Failed_1/2.png)

* KeyRepDesc & MouseRepDesc 搞反了，長度也沒對上
    ![alt text](Image/Fail/Failed_1/3.png)

    ![alt text](Image/Fail/Failed_1/4.png)

幸運的是這裡的錯誤改完後就可以成功讓滑鼠模仿 G402 的移動了!
不幸的是，這只是模擬滑鼠移動，還沒考慮到 GHUB 的存在，考慮上 GHUB，整體的難度會大幅提升

---

## 關於 GHUB 與更詳細的運作

前面的分析與模擬基本上都是沒有考慮上 GHUB 的存在，GHUB 讓滑鼠有更多的功能，例如 RGB 燈光，前面分析只有基本的滑鼠功能

要完全模擬 G402 還得過 GHUB 這一關，一種是去分析 GHUB 怎麼和滑鼠交互，另一種是直接看開源的專案: https://github.com/libratbag/libratbag/tree/master, 逆向佬幫忙把完整的協議挖出來給大家，問題是 code 量很大，AI 也會漏東漏西

目前我想到的策略是爆破所有 request，然後看有哪些 response，類似動態分析

在這之前必須好好理解整個運作流程，以下的結果是搭配 gemini 與手動實驗，多次迭代驗證得出的結果

---



前面看 HID Report Descriptor 有兩個，分別是 Interface 0/1
mouse 是 Interface 0 (59B)，keyboard 是 Interface 1 (179B)

看 Interface 1，會看到兩個 [廠商定義裝置]，一個是 Col04，一個是 Col05

![alt text](Image/USBTreeViewer/1.png)

對應 wireshark

![alt text](Image/Wireshark/8.png)

可以看到: Report ID 的差異 0x10, 0x11 分別對應 GHUB 的 短, 長指令

意思是 G402 的 Interface 1 有兩個窗口 Col4/Col5 分別處理長指令和短指令

---

```mermaid
graph TD
    subgraph PC_Side ["電腦端 (Windows 作業系統)"]
        G["G HUB / 你的 Python 腳本"]
        
        subgraph Windows_Virtual ["Windows HID 虛擬窗口 (由 179B 地圖生成)"]
            Col01_03["Col01~03<br>鍵盤/媒體/系統"]
            Col04["Col04 窗口<br>營業項目: 僅限發送短指令<br>(Report ID: 0x10 / 7B)"]
            Col05["Col05 窗口<br>營業項目: 發送長指令<br>⚠️ 接收所有回覆<br>(Report ID: 0x11 / 20B)"]
        end
        
        W["Windows USB 核心驅動"]
    end

    subgraph Mouse_Side [滑鼠端 / CH32V307]
        MCU((USB 控制器))
        EP0["總機 (Endpoint 0)<br>處理所有 Interface 的掛號信"]
        
        subgraph IF0 ["Interface 0: 標準滑鼠部門"]
            EP1["端點 1 (Interrupt IN)<br>只傳座標 ID: 0x01"]
            Sensor[光學感測器]
        end
        
        subgraph IF1 ["Interface 1: 複合部門 (MI_01)"]
            EP2["端點 2 (Interrupt IN)<br>傳送羅技回覆與巨集"]
            HID["HID++ 2.0 處理引擎"]
        end
    end

    %% 控制流
    G -- "發送 0x10 短指令" --> Col04
    G -- "發送 0x11 長指令" --> Col05
    Col04 -- "核准放行 7B" --> W
    Col05 -- "核准放行 20B" --> W
    W -- "SET_REPORT (wIndex=1)" --> EP0
    EP0 -- "轉交指令給 IF1" --> HID
    
    %% 數據流
    Sensor -. "產生座標" .-> EP1
    HID -. "⚠️ 統一產生 0x11 長回覆 (20B)" .-> EP2
    EP1 -- "無郵戳" --> W
    EP2 -- "無郵戳" --> W
    W -- "轉交長回覆" --> Col05
    Col05 -. "成功讀取 20B (0x11開頭)" .-> G

    classDef ep fill:#E74C3C,stroke:#C0392B,stroke-width:2px,color:#FFFFFF,font-weight:bold;
    classDef core fill:#3498DB,stroke:#2980B9,stroke-width:2px,color:#FFFFFF,font-weight:bold;
    classDef win fill:#F1C40F,stroke:#F39C12,stroke-width:2px,color:#333333,font-weight:bold;
    class EP0,EP1,EP2 ep;
    class HID core;
    class Col04,Col05 win;
```

特別的是
* 雖然 request 有長短指令之分，但 response 卻統一使用 0x11 長指令格式
* 而且有前門(EP0)入，後門(EP2)出的感覺

---


```mermaid
sequenceDiagram
    autonumber
    participant PC as 電腦 (Windows)
    participant GHUB as 官方軟體 (G HUB/Python)
    participant EP0 as 總機 (EP0)
    participant IF0 as 滑鼠部門 (Interface 0)
    participant IF1 as 複合部門 (Interface 1 / EP2)

    rect rgba(11, 105, 246, 0.1)
    Note over PC, IF1: 第一階段：列舉報到 (以 Wireshark Frame 25-54 為準)
    PC->>EP0: [Frame 25] GET DESCRIPTOR (DEVICE)
    EP0-->>PC: [Frame 26] 我是 VID:046D, PID:C07E
    
    PC->>EP0: [Frame 29] GET DESCRIPTOR (CONFIGURATION)
    EP0-->>PC: [Frame 30] 真相揭曉：我只有 2 個 Interface：IF0(滑鼠), IF1(私有/鍵盤)
    
    PC->>EP0: [Frame 47 & 53] GET DESCRIPTOR (HID Report)
    EP0-->>PC: [Frame 54] IF1 的 179B 地圖讓 Windows 生成了多個 Col (Col04 綁 0x10，Col05 綁 0x11)
    end

    rect rgba(5, 39, 174, 0.1)
    Note over PC, IF1: G HUB 發送「短指令 (0x10)」 - 走 Col04 窗口
    GHUB->>PC: 對 Col04 發送 [10 ff 00 1e 00 00 00] (共 7 Bytes)
    PC->>EP0: [Frame 88] SET_REPORT (wIndex: 1, ID: 0x10)
    EP0-->>PC: [Frame 91] ACK (總機已收下，轉交 IF1 處理)
    PC->>IF1: [Frame 92] (輪詢 EP2) IF1，短指令處理好了嗎？
    IF1-->>GHUB: ⚠️ 設備硬體強制以長指令格式回覆！透過 Col05 回傳 20 Bytes: 11 ff...
    end

    rect rgba(5, 5, 125, 0.1)
    Note over PC, IF1: G HUB 發送「長指令 (0x11)」 - 走 Col05 窗口
    GHUB->>PC: 對 Col05 發送 [11 ff 00 1e...] (共 20 Bytes)
    PC->>EP0: SET_REPORT (wIndex: 1, ID: 0x11)
    EP0-->>PC: ACK (總機已收下)
    PC->>IF1: (輪詢 EP2) IF1，長指令處理好了嗎？
    IF1-->>GHUB: 正常透過 Col05 回傳 20 Bytes: 11 ff...
    end
```

---

```mermaid
mindmap
  root((USB 封包))
    L1[外層 USB 郵戳]
      req(bmRequestType)
        req1[0x80 或 0x81 標準請求]
        req2[0x21 SET_REPORT 寫入]
          tip(👉 G HUB 發送點)
        req3[0xA1 GET_REPORT 讀取]
    L2[中層 HID 標籤]
      rep(Report ID)
        rep1[0x01 標準座標 8B]
        rep2[0x10 短指令 7B]
          c4(👉 僅限走 Col04 窗口發送)
        rep3[0x11 長指令 20B]
          c5(👉 走 Col05 窗口發送)
          c5_recv(⚠️ 設備所有回覆皆統一使用此 ID 接收)
        rep4[0x12 超長指令 64B]
    L3[內層 羅技門牌]
      feat(Feature Index)
        feat1[0x00 Root 總機]
        feat2[0x01 FeatureSet 清單]
        feat3[0x0F DPI 控制]
        feat4[0x81 Profile 記憶體]
    L4[核心 動作參數]
      func(Function ID)
        func1[0 Get 讀取]
        func2[1 Set 寫入]
      swid(Software ID)
      param(Parameters)

```

---

至此可以大概知道怎麼發封包
[Gemini 實作的腳本](tools/HID_requster.py)
