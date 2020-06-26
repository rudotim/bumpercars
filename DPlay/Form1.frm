VERSION 5.00
Object = "{4472AFD6-EAB8-448B-8207-A6CB40FF6F62}#1.0#0"; "DPLAY.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   2460
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4035
   LinkTopic       =   "Form1"
   ScaleHeight     =   2460
   ScaleWidth      =   4035
   StartUpPosition =   3  'Windows Default
   Begin DPlay.DPlayControl DPlayControl1 
      Left            =   840
      Top             =   120
      _ExtentX        =   2143
      _ExtentY        =   1720
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()

Dim B As Boolean
Dim yo As Long

B = DPlayControl1.Initialize_With_Port(113, "127.0.0.1")
'Debug.Print B
B = DPlayControl1.Create_Session(4, "Bills")
'Debug.Print B
yo = DPlayControl1.Create_Player("Chris")
yo = DPlayControl1.Create_Player("Dude")
'Debug.Print yo

End Sub
