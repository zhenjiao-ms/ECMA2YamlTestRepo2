    Public Sub DrawVisualStyleElementScrollBarThumbButtonHorizontal3(ByVal e As PaintEventArgs)
        If (VisualStyleRenderer.IsElementDefined( _
         VisualStyleElement.ScrollBar.ThumbButtonHorizontal.Pressed)) Then
            Dim renderer As New VisualStyleRenderer _
              (VisualStyleElement.ScrollBar.ThumbButtonHorizontal.Pressed)
            Dim rectangle1 As New Rectangle(10, 50, 50, 50)
            renderer.DrawBackground(e.Graphics, rectangle1)
            e.Graphics.DrawString("VisualStyleElement.ScrollBar.ThumbButtonHorizontal.Pressed", _
              Me.Font, Brushes.Black, New Point(10, 10))
        Else
            e.Graphics.DrawString("This element is not defined in the current visual style.", _
              Me.Font, Brushes.Black, New Point(10, 10))
        End If
    End Sub