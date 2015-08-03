
# 基礎篇 ： 事件

事件讓 WF8266R 自主處理一些簡易的控制, 不需要長期開啟 APP 或 網頁監控. 整體而言, 事件的設計分為2大部份, 第1是監聽, 第2是觸發. 目前監聽提供了 GPIO 和 時間 二種. 觸發提供 GPIO輸出 REQUEST 和 WebSocket 事件訂閱 3 種. 組合起來就有 6 種行為可供操作.

首先到 [開發手冊](http://code.unumobile.com/wf8266r/docs/WebAPI) 中查看 Events 分頁.


## 建立事件


### 案例 1 : 按下 WF8266R(GPIO0) 白色按鍵後關閉 GPIO5 上的 LED 燈
這裡有個關念要說明, 在按鍵電路上 WF8266R 的 GPIO 0 4 5 12 13 都是輸出高電位, 所以判別條件都是以低電位做為依據. 將上述目的轉換為 Event 參數如下:
```javascript
eventType=1        //預設值可不填
eventValue=0,0     //GPIO0 = 0 時成立
trigerType=1       //使用腳位觸發動作
trigerValue=5,0    //觸發腳為 GPIO5 輸出低電位

http://wf8266r.local/when/listen?eventValue=0,0&trigerType=1&trigerValue=5,0
```
接下來試看看吧, 按下白色按鍵, LED 燈就會熄滅了. 不過此時事件是沒有寫到記憶體中的, 因此重開或斷電就會遺失, 需要重新指定. 因此您可以透過以下方式寫入
```
http://wf8266r.local/save
```
###案例 2 : 按下 WF8266R(GPIO0) 白色按鍵後關閉 GPIO5 上的 LED 燈, 5秒後再亮起
現在 LED 燈是熄滅的狀態, 但希望 5 秒後再亮起, 我們可以使用 timer 來控制
```javascript
eventType=1        //預設值可不填
eventValue=0,0     //GPIO0 = 0 時成立
trigerType=1       //使用腳位觸發動作
trigerValue=5,1    //觸發腳為 GPIO5 輸出低電位
timer=5000         //成立後5秒觸發

http://wf8266r.local/when/listen?eventValue=0,0&trigerType=1&trigerValue=5,1&timer=5000
```
同樣的將這組設定 SAVE 到記憶體中, 你可以重開 WF8266R 再試一次.
###案例 3 : 按下 WF8266R(GPIO0) 白色按鍵後關閉另一塊 WF8266R GPIO5 上的 LED 燈

另一塊 WF8266R 的 IP為 192.168.0.21 使用 WebAPIs 方式控制 GPIO, 我們可以這樣使用 :
```
http://192.168.0.21/gpio?5=0
```
在了解之後, 轉換為事件參數如下 :
```javascript
eventType=1                             //預設值可不填
eventValue=0,0                          //GPIO0 = 0 時成立
trigerType=2                            //使用 Request 觸發動作, 位址一定要最後做
trigerValue=192.168.0.21:80,gpio?5=0    //觸發另一塊 WF8266R 腳為 GPIO5 輸出低電位

http://wf8266r.local/when/listen?eventValue=0,0&trigerType=2&trigerValue=192.168.0.21:80,gpio?5=0
```
###案例 4 : 按下 WF8266R(GPIO0) 白色按鍵後 發一封信到指定信箱
發信到指定信箱是和案例 3 使用相同的 Request 但要求的目標不同, 這裡使用的是 WF8266R 的 Mail 服務
```
http://code.unumobile.com/wf8266r/api/mail/device/{email}/{title}/{templateID}
```
其中的 {email} 是收信位址, {title} 是標題. 這裡要注意, 為了減少 WF8266R 記憶體使用, 因此使用 GET 方式, 所以 TITLE 長度盡量不要超過 10.

{templateID} 是通知範本編號, 沒有請輸入0

在了解之後, 轉換為事件參數如下 :
```javascript
eventType=1                             //預設值可不填
eventValue=0,0                          //GPIO0 = 0 時成立
trigerType=2                            //使用 Request 觸發動作, 位址一定要最後做

//傳送 Email 到 sample@unumobile.com 標題為 GPIO0 Alarm
trigerValue=code.unumobile.com:80,wf8266r/api/mail/device/sample@unumobile.com/GPIO0%20Alarm/0    

index=3                                 //使用修改 將新的設定指到 3 號位址

http://wf8266r.local/when/listen?eventValue=0,0&trigerType=2&trigerValue=code.unumobile.com:80,wf8266r/api/mail/device/sample@unumobile.com/GPIO0%20Alarm/0&index=3
```
其中我們使用了 index 修改事件的 TAG, 為確保 WF8266R 的穩定, 目前 REQUEST 同時只能有一個連線, 因此需要覆寫到案例 3 的事件位址, 不然這個動作將無法被觸發, 因為會先呼叫案例 3.
###案例 5 : 按下 WF8266R(GPIO0) 白色按鍵後通知網頁端訂閱者 PIN0_Click
事件訂閱會需要使用到 WF8266R.js 的 GPIO 物件. 透過 e.Action 獲得目前通知的事件名
```javascript
GPIO.events(function(e){
    $("#message").text(e.Action).fadeIn().delay(100).fadeOut();
});
```
在了解之後, 轉換為事件參數如下 :
```javascript
eventType=1                             //預設值可不填
eventValue=0,0                          //GPIO0 = 0 時成立
trigerType=3                            //使用 WebSocket 通知訂閱者
trigerValue=PIN0_Click                  //自訂事件名稱 傳送到 GPIO.events 裡的 e.Action

http://wf8266r.local/when/listen?eventValue=0,0&trigerType=3&trigerValue=PIN0_Click
```
[**查看完整範例**](http://code.unumobile.com/wf8266r/Default?templateName=07_Events.html)

###案例 6 : 每個小時的 0 分 關閉 LED, 5 分 打開 LED
時間的監控是使用 eventType=2

在了解之後, 轉換為事件參數如下 :
```javascript
eventType=2                             //時間監控
eventValue=:0                           //時間的分鐘數 = 0 時成立
trigerType=1                            //使用腳位輸出
trigerValue=5,0                         //將 GPIO5 輸出低電位

// 0 分時關閉
http://wf8266r.local/when/listen?eventType=2&eventValue=:0&trigerType=1&trigerValue=5,0
// 5 分時打開
http://wf8266r.local/when/listen?eventType=2&eventValue=:5&trigerType=1&trigerValue=5,1
// 晚上 8 點 使用 WebSocket 訂閱通知
http://wf8266r.local/when/listen?eventType=2&eventValue=20:0&trigerType=3&trigerValue=PM8
```


## 查看事件
```
http://wf8266r.local/when
```
```javascript
{"events":[
{"eventIndex":1,"eventType":1,"eventValue":"0,0","trigerType":1,"trigerValue":"5,0","timer":0,"state":0,"times":255},
{"eventIndex":2,"eventType":1,"eventValue":"0,0","trigerType":1,"trigerValue":"5,1","timer":5000,"state":0,"times":255},
{"eventIndex":3,"eventType":1,"eventValue":"0,0","trigerType":3,"trigerValue":"PIN0_Click","timer":0,"state":0,"times":255},
{"eventIndex":4,"eventType":1,"eventValue":"0,0","trigerType":2,"trigerValue":"code.unumobile.com:80,wf8266r/api/mail/device/sample@unumobile.com/GPIO0 Alarm/0","timer":0,"state":0,"times":255},
{"eventIndex":5,"eventType":2,"eventValue":":0","trigerType":1,"trigerValue":"5,0","timer":0,"state":0,"times":255},
{"eventIndex":6,"eventType":2,"eventValue":":5","trigerType":1,"trigerValue":"5,1","timer":0,"state":0,"times":255},
{"eventIndex":7,"eventType":2,"eventValue":"20:0","trigerType":3,"trigerValue":"PM8","timer":0,"state":0,"times":255}
]}
```

## 修改事件

透過 &index=n 其中 n 為 eventIndex 編號 1~6

##清空事件
```
http://wf8266r.local/when?=
```

##永久儲存事件
```
http://wf8266r.local/save
```