VERSION 5.00
Begin VB.UserControl DPlayControl 
   ClientHeight    =   810
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   1065
   InvisibleAtRuntime=   -1  'True
   ScaleHeight     =   810
   ScaleWidth      =   1065
   Windowless      =   -1  'True
   Begin VB.Label Label1 
      Caption         =   "DirectPlay"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   855
   End
   Begin VB.Image Image1 
      Height          =   480
      Left            =   240
      Picture         =   "DPlayControl.ctx":0000
      Top             =   240
      Width           =   480
   End
End
Attribute VB_Name = "DPlayControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True



Private Sub UserControl_Initialize()

'When a Multiplayer dialog is opened, this is called, which
'initializes our DirectPlay object

InitDPlay

End Sub


Private Sub UserControl_Terminate()

'This deallocates resources when the dialog is closed

CloseDownDPlay

End Sub

'Every connection in DirectPlay must have an address. With this
'function, we can initialize an address for a given method
'of connecting.  The methods of connecting are TCP/IP, IPX, etc.
'In the C++ file Multiplayer.cpp there is a #define section
'which identifies each of these connection methods as an
'integer.  This is the WhichConnection parameter.

Public Function Initialize_Connection(WhichConnection As Integer) As Boolean

Dim objDPAddress As DirectPlayAddress

'In most of these functions, if anything goes wrong, we
'return FALSE as the value of the function.

On Error GoTo ERRORMSG
Set objDPAddress = gObjEnumConnections.GetAddress(WhichConnection)
Call gObjDPlay.InitializeConnection(objDPAddress)

Initialize_Connection = True
Exit Function

ERRORMSG:
    Initialize_Connection = False

End Function

'When a session is created, certain DirectPlay flags must
'be set, and the GUID must be given to the session.  This
'function does all of this, using the best parameters for
'a Bumper Cars game.  The maximum number of players and the
'session name are passed in as parameters.

Public Function Create_Session(MaxPlayers As Integer, SessionName As String) As Boolean

Dim SessionData As DirectPlaySessionData

On Error GoTo ERRORMSG
Set SessionData = gObjDPlay.CreateSessionData
Call SessionData.SetMaxPlayers(MaxPlayers)
Call SessionData.SetSessionName(SessionName)
Call SessionData.SetGuidApplication(AppGuid)

'If the machine starting the game is disconnected, use
'another player as host
Call SessionData.SetFlags(DPSESSION_MIGRATEHOST)

'Use TCP packets rather than UDP
Call SessionData.SetFlags(DPSESSION_DIRECTPLAYPROTOCOL)

'Turn message throttling off
Call SessionData.SetFlags(DPSESSION_OPTIMIZELATENCY)

'This brings up the dialog which asks for an IP address
Set gObjDPEnumSessions = gObjDPlay.GetDPEnumSessions(SessionData, 0, DPENUMSESSIONS_AVAILABLE)

'Finally, create the session
Call gObjDPlay.Open(SessionData, DPOPEN_CREATE)

Create_Session = True
Exit Function

ERRORMSG:
    Create_Session = False

End Function

'This is similar to Create_Session except we join instead.

Public Function Join_Session() As Boolean

Dim SessionData As DirectPlaySessionData
Dim SessionData1 As DirectPlaySessionData

On Error GoTo ERRORMSG
Set SessionData = gObjDPlay.CreateSessionData
Call SessionData.SetGuidApplication(AppGuid)
Set gObjDPEnumSessions = gObjDPlay.GetDPEnumSessions(SessionData, 0, DPENUMSESSIONS_AVAILABLE)

'We get the first DirectPlay session on the remote machine.
'If more than one session (example:  another game entirely)
'is using DirectPlay, this could act flaky.  This small bug
'should be fixed in the future, but is left in for now.
Set SessionData1 = gObjDPEnumSessions.GetItem(1)

'Join the session
Call gObjDPlay.Open(SessionData1, DPOPEN_JOIN)

Join_Session = True
Exit Function

ERRORMSG:
    Join_Session = False

End Function

'Creating a player is easy, by just calling DirectPlay's
'function for it.  Since there can be two players on any one
'machine, we only want to save one of their ID numbers.
'(Why is more apparent in the Visual C++ Code)

Public Function Create_Player(PlayerName As String) As Long

Dim PlayerHandle As String
Dim Temp As Long

'Player handles are not used by us, so we just set it to
'a default value
PlayerHandle = "Player"

Temp = gPlayerID
gPlayerID = gObjDPlay.CreatePlayer(PlayerName, PlayerHandle, 0, 0)

'We create the player and then return the ID
'Note that a return value of 0 indicates a problem
Create_Player = gPlayerID

'Only save the first player's ID #
If (Temp <> 0) Then
    gPlayerID = Temp
End If

End Function

'Sometimes it is necessary to destroy a player.  DirectPlay
'facilitates this by providing a DestroyPlayer function.
'The ID # of the player being destroyed is needed as a
'parameter.

Public Function Destroy_Player(PlayerID As Long) As Boolean

On Error GoTo ERRORMSG
Call gObjDPlay.DestroyPlayer(PlayerID)

Destroy_Player = True
Exit Function

ERRORMSG:
    Destroy_Player = False

End Function

'This returns a count of all players connected.

Public Function Get_Num_Players_Connected() As Integer

Get_Num_Players_Connected = _
    gObjDPlay.GetDPEnumPlayers("", 0).GetCount
 
End Function

'This returns any ID for a given player WhichPlayer.

Public Function Get_PlayerID(WhichPlayer As Integer) As Long

Get_PlayerID = _
    gObjDPlay.GetDPEnumPlayers("", 0).GetDPID(WhichPlayer)

End Function

'And this returns any name for a given player.

Public Function Get_Player_Name(WhichPlayer As Integer) As String

Get_Player_Name = _
    gObjDPlay.GetDPEnumPlayers("", 0).GetShortName(WhichPlayer)

End Function

'It is very useful to know how many messages are waiting for
'you in your queue.  This function returns this number.

Public Function Get_Message_Count() As Long

Get_Message_Count = _
    gObjDPlay.GetMessageCount(gPlayerID)

End Function

'During the game, we send position messages to everybody
'playing.  We send the car number, its direction, x and y
'values, and its speed to all the players.

Public Function Send_Position_Message_To_All(Car As Integer, Direct As Integer, XPos As Double, YPos As Double, Accel As Double) As Boolean

Dim dpMsg As DirectPlayMessage

On Error GoTo ERRORMSG
Set dpMsg = gObjDPlay.CreateMessage

'When sending a message, we write the type of message first.
'MPOSITION in reality translates to an integer value which
'is at the head of the message.
Call dpMsg.WriteLong(MPOSITION)

'Now write other info to the message
Call dpMsg.WriteLong(Car)
Call dpMsg.WriteLong(Direct)
Call dpMsg.WriteDouble(XPos)
Call dpMsg.WriteDouble(YPos)
Call dpMsg.WriteDouble(Accel)

'Send it to all players, guaranteed
Call gObjDPlay.Send(gPlayerID, DPID_ALLPLAYERS, DPSEND_GUARANTEED, dpMsg)

Send_Position_Message_To_All = True
Exit Function

ERRORMSG:
    Send_Position_Message_To_All = False

End Function

'Many of the Send_[Something]_Message_To_All functions are
'very similar in form.  This is another one which sends a
'chat message to all the players playing.

Public Function Send_Chat_Message_To_All(Message As String) As Boolean

Dim dpMsg As DirectPlayMessage

On Error GoTo ERRORMSG
Set dpMsg = gObjDPlay.CreateMessage
Call dpMsg.WriteLong(CHAT)
Call dpMsg.WriteString(Message)

Call gObjDPlay.Send(gPlayerID, DPID_ALLPLAYERS, DPSEND_GUARANTEED, dpMsg)

Send_Chat_Message_To_All = True
Exit Function

ERRORMSG:
    Send_Chat_Message_To_All = False

End Function

'Another send message, this time a start message is sent to
'remote machines.  The game board being used, total players,
'game mode, and time limit/number of laps are also sent to
'all players playing.

Public Function Send_Start_Message_To_All(TotalPlay As Integer, Board As Integer, Mode As Integer, ExtraData As Integer) As Boolean

Dim dpMsg As DirectPlayMessage

On Error GoTo ERRORMSG
Set dpMsg = gObjDPlay.CreateMessage
Call dpMsg.WriteLong(MSTART)
Call dpMsg.WriteLong(TotalPlay)
Call dpMsg.WriteLong(Board)
Call dpMsg.WriteLong(Mode)
Call dpMsg.WriteLong(ExtraData)

Call gObjDPlay.Send(gPlayerID, DPID_ALLPLAYERS, DPSEND_GUARANTEED, dpMsg)

Send_Start_Message_To_All = True
Exit Function

ERRORMSG:
    Send_Start_Message_To_All = False

End Function

'When a player is bumped, a message is sent to his car to
'raise damage and move either backwards or forwards.
'This message sends the message to everyone playing, with
'the Car parameter being used to distinguish the car being
'bumped.

Public Function Send_Bump_Message_To_All(Car As Integer, Dam As Integer, goFor As Boolean) As Boolean

Dim dpMsg As DirectPlayMessage

On Error GoTo ERRORMSG
Set dpMsg = gObjDPlay.CreateMessage
Call dpMsg.WriteLong(BUMPED)
Call dpMsg.WriteLong(Car)
Call dpMsg.WriteLong(Dam)
Call dpMsg.WriteLong(goFor)

Call gObjDPlay.Send(gPlayerID, DPID_ALLPLAYERS, DPSEND_GUARANTEED, dpMsg)

Send_Bump_Message_To_All = True
Exit Function

ERRORMSG:
    Send_Bump_Message_To_All = False

End Function

'When a player wins the game, we want to send a winner
'message to all players, so the information can be displayed
'on screen.

Public Function Send_Winner_Message_To_All(Car As Integer, Name As String) As Boolean

Dim dpMsg As DirectPlayMessage

On Error GoTo ERRORMSG
Set dpMsg = gObjDPlay.CreateMessage
Call dpMsg.WriteLong(WINNER)
Call dpMsg.WriteLong(Car)
Call dpMsg.WriteString(Name)

Call gObjDPlay.Send(gPlayerID, DPID_ALLPLAYERS, DPSEND_GUARANTEED, dpMsg)

Send_Winner_Message_To_All = True
Exit Function

ERRORMSG:
    Send_Winner_Message_To_All = False

End Function

'This is sent when a power-up needs to be drawn on a remote
'screen.

Public Function Send_Draw_Message_To_All(WhichPowerUp As Integer, XPos As Integer, YPos As Integer) As Boolean

Dim dpMsg As DirectPlayMessage

On Error GoTo ERRORMSG
Set dpMsg = gObjDPlay.CreateMessage
Call dpMsg.WriteLong(DRAWPUP)
Call dpMsg.WriteLong(WhichPowerUp)
Call dpMsg.WriteLong(XPos)
Call dpMsg.WriteLong(YPos)

Call gObjDPlay.Send(gPlayerID, DPID_ALLPLAYERS, DPSEND_GUARANTEED, dpMsg)

Send_Draw_Message_To_All = True
Exit Function

ERRORMSG:
    Send_Draw_Message_To_All = False

End Function

'And this is sent when a player captures a power-up and it
'no longer needs to be drawn.

Public Function Send_Undraw_Message_To_All(WhichPowerUp As Integer, XPos As Integer, YPos As Integer) As Boolean

Dim dpMsg As DirectPlayMessage

On Error GoTo ERRORMSG
Set dpMsg = gObjDPlay.CreateMessage
Call dpMsg.WriteLong(UNDRAWPUP)
Call dpMsg.WriteLong(WhichPowerUp)
Call dpMsg.WriteLong(XPos)
Call dpMsg.WriteLong(YPos)

Call gObjDPlay.Send(gPlayerID, DPID_ALLPLAYERS, DPSEND_GUARANTEED, dpMsg)

Send_Undraw_Message_To_All = True
Exit Function

ERRORMSG:
    Send_Undraw_Message_To_All = False

End Function

'This is sent when a player captures the flag during capture
'the flag mode.

Public Function Send_Acquire_Message_To_All(Car As Integer) As Boolean

Dim dpMsg As DirectPlayMessage

On Error GoTo ERRORMSG
Set dpMsg = gObjDPlay.CreateMessage
Call dpMsg.WriteLong(MACQUIRE)
Call dpMsg.WriteLong(Car)

Call gObjDPlay.Send(gPlayerID, DPID_ALLPLAYERS, DPSEND_GUARANTEED, dpMsg)

Send_Acquire_Message_To_All = True
Exit Function

ERRORMSG:
    Send_Acquire_Message_To_All = False

End Function

'This is sent when a player loses the flag during capture
'the flag mode.

Public Function Send_UnAcquire_Message_To_All() As Boolean

Dim dpMsg As DirectPlayMessage

On Error GoTo ERRORMSG
Set dpMsg = gObjDPlay.CreateMessage
Call dpMsg.WriteLong(MUNACQUIRE)

Call gObjDPlay.Send(gPlayerID, DPID_ALLPLAYERS, DPSEND_GUARANTEED, dpMsg)

Send_UnAcquire_Message_To_All = True
Exit Function

ERRORMSG:
    Send_UnAcquire_Message_To_All = False

End Function


'After GetDPMessage has been called, many variables are stored
'in memory.  The numerous Get_[Something]_Message functions
'are used to retrieve these values.
'This first one retrieves a chat message that was sent.

Public Function Get_Chat_Message() As String

Get_Chat_Message = ChatMessage

End Function

'When a game starts, data such as track layout, number of
'players, etc. is given to all players.  This retrieves the
'information.

Public Function Get_Total_Players() As Integer

Get_Total_Players = TotalPlayers

End Function

'Retrieve a position message.

Public Sub Get_Position_Message(ByRef Car As Integer, ByRef Direct As Integer, ByRef XPos As Double, ByRef YPos As Double, ByRef Accel As Double)

Car = WhichCar
Direct = Direction
XPos = XPosition
YPos = YPosition
Accel = Acceleration

End Sub

'Retrieve start data for a game.

Public Sub Get_Start_Message(ByRef TotalPlay As Integer, ByRef Board As Integer, ByRef Mode As Integer, ByRef ExtraData As Integer)

TotalPlay = TotalPlayers
Board = BoardChosen
Mode = GameMode
ExtraData = LapsTime

End Sub

'Retrieve data when you are bumped.

Public Sub Get_Bumped_Message(ByRef Car As Integer, ByRef Dam As Integer, ByRef goFor As Boolean)

Car = WhichCar
Dam = Damage
goFor = Forwards

End Sub

'When somebody wins, retrieve the data.

Public Sub Get_Winner_Message(ByRef Car As Integer, ByRef Name As String)

Car = WhichCar
Name = ChatMessage

End Sub

'When a power-up is drawn/undrawn, then retrieve the data.
'The same function is used for both because of their
'similarity.

Public Sub Get_PowerUp_Message(ByRef WhichPowerUp As Integer, ByRef XPos As Integer, ByRef YPos As Integer)

WhichPowerUp = TypeOfPowerUp
XPos = IntXPos
YPos = IntYPos

End Sub

'This retrieves whom has captured the flag.

Public Sub Get_Acquire_Message(ByRef Car As Integer)

Car = WhichCar

End Sub



'This initializes players with a certain port in mind.  This
'can be used to circumvent firewalls when only certain ports
'are allowed to send data, since DirectPlay does not usually
'work behind a firewall.  This is not currently implemented
'in the current Bumper Cars but is left in for future
'considerations.
'
'Public Function Initialize_With_Port(Port As Long, IP As String) As Boolean
'
'Dim objDPAddress As DirectPlayAddress
'
'On Error GoTo ERRORMSG
'Set objDPAddress = gDPLobby.CreateINetAddress(IP, Port)
'Call gObjDPlay.InitializeConnection(objDPAddress)
'
'Initialize_With_Port = True
'Exit Function
'
'
'ERRORMSG:
'    Initialize_With_Port = False
'
'End Function







'GetDPMessage is the lynchpin which holds the whole process
'here together.  GetDPMessage reads in a message, extracts
'the data out of it, and tells the code calling it exactly what
'type of message it received.

Public Function GetDPMessage() As Integer

Dim MsgCount As Long
Dim dpMsg As DirectPlayMessage
Dim FromPlayerID As Long
Dim ToPlayerID As Long

' If this call fails, presumably it's because there's no
'session or no player.
If gObjDPlay Is Nothing Then Exit Function

'Make sure we actually have a message in our queue
MsgCount = gObjDPlay.GetMessageCount(gPlayerID)

If MsgCount > 0 Then
  
    'Retrieve one message at a time, even though the flag
    'is DPRECEIVE_ALL.  My understanding is that DirectPlay
    'only removes one message from the queue when this flag
    'is set.  It also works this way in practice.
    Set dpMsg = gObjDPlay.Receive(FromPlayerID, ToPlayerID, DPRECEIVE_ALL)
    
    'We want to read in the type of message (that is why we
    'always sent the type of message first)
    MsgType = dpMsg.ReadLong()
    
    'If we get a system message from DirectPlay, then usually
    'it is a change in the number of players.  Return 0
    'as the type of message.
    If FromPlayerID = DPID_SYSMSG Then
        GetDPMessage = 0
    Else
    Select Case MsgType
        'If a chat message is received, then read in the
        'message and return 1.  Many of the other cases are
        'similar:  read in values and return a unique number
        'identifying that message.
        
        Case CHAT
            ChatMessage = dpMsg.ReadString()
            GetDPMessage = 1
        Case MPOSITION
            WhichCar = dpMsg.ReadLong()
            Direction = dpMsg.ReadLong()
            XPosition = dpMsg.ReadDouble()
            YPosition = dpMsg.ReadDouble()
            Acceleration = dpMsg.ReadDouble()
            GetDPMessage = 2
        Case MSTART
            TotalPlayers = dpMsg.ReadLong()
            BoardChosen = dpMsg.ReadLong()
            GameMode = dpMsg.ReadLong()
            LapsTime = dpMsg.ReadLong()
            GetDPMessage = 3
        Case BUMPED
            WhichCar = dpMsg.ReadLong()
            Damage = dpMsg.ReadLong()
            Forwards = dpMsg.ReadLong()
            GetDPMessage = 4
        Case WINNER
            WhichCar = dpMsg.ReadLong()
            ChatMessage = dpMsg.ReadString()
            GetDPMessage = 5
        Case DRAWPUP
            TypeOfPowerUp = dpMsg.ReadLong()
            IntXPos = dpMsg.ReadLong()
            IntYPos = dpMsg.ReadLong()
            GetDPMessage = 6
        Case UNDRAWPUP
            TypeOfPowerUp = dpMsg.ReadLong()
            IntXPos = dpMsg.ReadLong()
            IntYPos = dpMsg.ReadLong()
            GetDPMessage = 7
        Case MACQUIRE
            WhichCar = dpMsg.ReadLong()
            GetDPMessage = 8
        Case MUNACQUIRE
            GetDPMessage = 9
        Case Else
            'Do nothing, as no other message types should
            'be sent
    End Select
    End If
End If

End Function

'A question to ask is: why do we bother to read in the values
'and not pass them back right away?  Well, when a message is
'received, we have no way of knowing what type of message it
'is.  So, how would the function be written?  Would the return
'value be a string (CHAT) or many values (the others)?  Without
'having to do void pointers and such, storing the values and
'then retreiving them was the easiest algorithm we could think
'of.

