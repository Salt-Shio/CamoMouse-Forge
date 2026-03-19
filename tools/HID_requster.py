import hid
import time

def find_logitech_hidpp_interfaces():
    """尋找羅技 HID++ (Usage Page 0xFF00) 的所有裝置路徑"""
    paths = []
    # 羅技的 Vendor ID 通常是 0x046D
    for device in hid.enumerate(0x046d):
        if device['usage_page'] == 0xff00:
            paths.append(device['path'])
    return paths

def test_dual_channel(col4_path, col5_path):
    """測試雙通道同時監聽與收發"""
    try:
        print(f"🔌 正在開啟通道...")
        print(f"   - 通道 A (Col04): {col4_path}")
        print(f"   - 通道 B (Col05): {col5_path}")

        dev_col4 = hid.device()
        dev_col4.open_path(col4_path)
        dev_col4.set_nonblocking(True)

        dev_col5 = hid.device()
        dev_col5.open_path(col5_path)
        dev_col5.set_nonblocking(True)

        # 清除前面的掃描可能殘留的緩衝區資料 (把舊的回覆吃掉)
        print("🧹 清除緩衝區殘留資料...")
        while dev_col4.read(20): pass
        while dev_col5.read(20): pass

        # 建立一個可以同時監聽兩個通道的輔助函數
        def listen_both(timeout=0.5):
            start_time = time.time()
            while time.time() - start_time < timeout:
                r4 = dev_col4.read(20)
                if r4: return "Col04", r4
                r5 = dev_col5.read(20)
                if r5: return "Col05", r5
                time.sleep(0.01)
            return None, None

        # --- 測試 1: 發送 0x10 短指令 ---
        request_10 = [0x10, 0xFF, 0x00, 0x1E, 0x00, 0x01, 0x00]
        request_str = ' '.join([f'{x:02x}' for x in request_10])
        print(f"\n📤 [測試 1 - Col04 發送] 7B 短指令: {request_str}")
        
        w = dev_col4.write(request_10)
        # 處理各平台 hidapi 寫入的差異 (有些需要補 0x00 Report ID)
        if w == -1: w = dev_col4.write(bytes(request_10))
        if w == -1: w = dev_col4.write([0x00] + request_10)
        
        if w == -1:
            print("❌ Col04 發送失敗！")
        else:
            print(f"👂 正在同時監聽 Col04 與 Col05...")
            ch, resp = listen_both()
            if resp:
                print(f"📥 [攔截成功] 🎉 收到回覆於 [{ch}]: {' '.join([f'{x:02x}' for x in resp])}")
            else:
                print("❌ [逾時] 沒有攔截到回覆。")

        # --- 測試 2: 發送 0x11 長指令 ---
        # 長指令通常是 20 bytes，扣除前面 6 bytes 標頭，後面補 14 個 0x00
        request_11 = [0x11, 0xFF, 0x00, 0x0D, 0x00, 0x01] + [0x00] * 14
        request_str_11 = ' '.join([f'{x:02x}' for x in request_11])
        print(f"\n📤 [測試 2 - Col05 發送] 20B 長指令: {request_str_11}")
        
        w = dev_col5.write(request_11)
        if w == -1: w = dev_col5.write(bytes(request_11))
        if w == -1: w = dev_col5.write([0x00] + request_11)
        
        if w == -1:
            print("❌ Col05 發送失敗！")
        else:
            print(f"👂 正在同時監聽 Col04 與 Col05...")
            ch, resp = listen_both()
            if resp:
                print(f"📥 [攔截成功] 🎉 收到回覆於 [{ch}]: {' '.join([f'{x:02x}' for x in resp])}")
            else:
                print("❌ [逾時] 沒有攔截到回覆。")

        # 關閉雙通道
        dev_col4.close()
        dev_col5.close()
        print("\n✅ 雙通道完整測試完成！")

    except Exception as e:
        print(f"❌ 執行發生錯誤: {e}")

if __name__ == "__main__":
    print("🔍 正在掃描羅技 HID++ 介面...")
    paths = find_logitech_hidpp_interfaces()
    
    if len(paths) >= 2:
        print(f"✅ 找到 {len(paths)} 個符合的 HID++ 通道，取前兩個進行測試。")
        test_dual_channel(paths[0], paths[1])
    else:
        print(f"❌ 找到的 HID++ 通道不足 (目前找到 {len(paths)} 個)。")
        print("請確認設備已正確連接，或是檢查您的系統權限。")