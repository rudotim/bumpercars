Attribute VB_Name = "GetMessages"
Public Sub GetDPMessages()

Dim MsgCount As Long
Dim dpMsg As DirectPlayMessage
Dim FromPlayerID As Long
Dim ToPlayerID As Long


If gObjDPlay Is Nothing Then Exit Sub

' If this call fails, presumably it's because there's no session or
' no player.
MsgCount = gObjDPlay.GetMessageCount(gPlayerID)

Do While MsgCount > 0
  
    Set dpMsg = gObjDPlay.Receive(FromPlayerID, ToPlayerID, DPRECEIVE_ALL)
    MsgType = dpMsg.ReadLong()
    MsgCount = MsgCount - 1
    
    If FromPlayerID = DPID_SYSMSG Then
        'Do nothing for now
    Else
    Select Case MsgType
        Case CHAT
            ChatMessage = dpMsg.ReadString()
            raiseevent ChatMessageReceived
        
        Case Else
            'Do nothing
    End Select
    End If
Loop

End Sub
