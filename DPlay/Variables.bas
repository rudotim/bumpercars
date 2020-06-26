Attribute VB_Name = "Variables"
'Here we declare some variables needed for the operation of
'the control.  These are, in a sense, private variables that
'the control uses to store information.


'Declare DirectX stuff
Public gObjDX As New DirectX7
Public gObjDPlay As DirectPlay4
Public gObjDPEnumSessions As DirectPlayEnumSessions
Public gObjEnumConnections As DirectPlayEnumConnections

'A GUID uniquely identifies the application to DirectPlay
Public Const AppGuid = "{8F8DECDE-868F-4562-B0FA-2AF475AC19E4}"

'The player's ID #
Public gPlayerID As Long

'Store the chat message if we get one
Public ChatMessage As String

'When a position message is received, we will get 5 values
'which are stored here
Public WhichCar As Integer
Public Direction As Integer
Public XPosition As Double
Public YPosition As Double
Public Acceleration As Double

'When a start message is received, store its info here
Public TotalPlayers As Integer
Public GameMode As Integer
Public BoardChosen As Integer
Public LapsTime As Integer

'Store a bumped message's info
Public Damage As Integer
Public Forwards As Boolean

'Store info for a draw/undraw power-up message
Public TypeOfPowerUp As Integer
Public IntXPos As Integer
Public IntYPos As Integer

'Different message types that can be received
Public Enum MessageType
    CHAT
    MPOSITION
    MSTART
    BUMPED
    WINNER
    DRAWPUP
    UNDRAWPUP
    MACQUIRE
    MUNACQUIRE

End Enum


Public Sub InitDPlay()

  'This is standard initialization for a DirectPlay object
  On Error GoTo FAILED
  Set gObjDPlay = gObjDX.DirectPlayCreate("")
  Set gDPLobby = gObjDX.DirectPlayLobbyCreate
  Set gObjEnumConnections = gObjDPlay.GetDPEnumConnections("", DPCONNECTION_DIRECTPLAY)
  Exit Sub

FAILED:
  MsgBox ("Failed to initialize DirectPlay.")

End Sub


Public Sub CloseDownDPlay()

  'The equivalent of 'deleting' our objects in C++
  Set gObjEnumConnections = Nothing
  Set gObjDPEnumSessions = Nothing
  Set gObjDPlay = Nothing
End Sub


