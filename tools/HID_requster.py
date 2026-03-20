import hid
import time

class USBTester:
    def __init__(self, col4, col5, timeout = 0.5):
        self.col4 = col4
        self.dev_col4 = hid.device()
        self.dev_col4.open_path(col4)
        self.dev_col4.set_nonblocking(True)

        self.col5 = col5
        self.dev_col5 = hid.device()
        self.dev_col5.open_path(col5)
        self.dev_col5.set_nonblocking(True)

        self.timeout = timeout

    def listen_both(self):
        start_time = time.time()
        while time.time() - start_time < self.timeout:
            r4 = self.dev_col4.read(20)
            if r4: return "Col04", r4
            r5 = self.dev_col5.read(20)
            if r5: return "Col05", r5
            time.sleep(0.01)
        return None, None

    def test_col4(self, request_packet):
        while self.dev_col4.read(20): pass 
        print(f"[Col04 發送] : {' '.join([f'{x:02x}' for x in request_packet])}")

        self.dev_col4.write(request_packet)
        col, read_data = self.listen_both()
        print(f"[{col} 接收] : {' '.join([f'{x:02x}' for x in read_data])}")

    def test_col5(self, request_packet):
        while self.dev_col5.read(20): pass
        print(f"[Col05 發送] : {' '.join([f'{x:02x}' for x in request_packet])}")

        self.dev_col5.write(request_packet)
        col, read_data = self.listen_both()
        print(f"[{col} 接收] : {' '.join([f'{x:02x}' for x in read_data])}")
        
    def __del__(self):
        print("END")
        self.dev_col4.close()
        self.dev_col5.close()
        

def get_logitech_hidpp_interfaces():
    """尋找羅技 HID++ (Usage Page 0xFF00) 的所有裝置路徑"""
    Col4 = None
    Col5 = None
    # 羅技的 Vendor ID 通常是 0x046D
    for device in hid.enumerate(0x046d):
        if device['usage_page'] == 0xff00:
            if b'Col04' in device["path"]: Col4 = device["path"] # short instruction
            elif b'Col05' in device["path"]: Col5 = device["path"] # long instruction

    return Col4, Col5

if __name__ == "__main__":
    print("正在掃描羅技 HID++ 介面...")
    Col4, Col5 = get_logitech_hidpp_interfaces()
    usb_tester = USBTester(Col4, Col5)
    
    request_packet = [0x10, 0xFF, 0x00, 0x1E, 0x00, 0x01, 0x00]
    usb_tester.test_col4(request_packet)

    print("-" * 10)

    request_packet = [0x11, 0xFF, 0x00, 0x0D, 0x00, 0x01] + [0x00] * 14
    usb_tester.test_col5(request_packet)