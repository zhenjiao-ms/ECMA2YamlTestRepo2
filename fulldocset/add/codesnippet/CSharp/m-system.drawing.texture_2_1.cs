        public void ScaleTransform_Example1(PaintEventArgs e)
        {
                     
            // Create a TextureBrush object.
            TextureBrush tBrush = new TextureBrush(new Bitmap("texture.jpg"));
                     
            // Scale the texture image 2X in the x-direction.
            tBrush.ScaleTransform(2, 1);
                     
            // Fill a rectangle with tBrush.
            e.Graphics.FillRectangle(tBrush, 0, 0, 100, 100);
        }