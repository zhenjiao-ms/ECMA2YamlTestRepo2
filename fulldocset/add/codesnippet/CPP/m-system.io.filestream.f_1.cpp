            // Update the file.
            case 'W':
               try
               {
                  fileStream->Seek( textLength, SeekOrigin::Begin );
                  fileStream->Read( readText, textLength - 1, byteCount );
                  tempString = gcnew String( uniEncoding->GetChars( readText, textLength - 1, byteCount ) );
                  recordNumber = Int32::Parse( tempString ) + 1;
                  fileStream->Seek( textLength, SeekOrigin::Begin );
                  fileStream->Write( uniEncoding->GetBytes( recordNumber.ToString() ), 0, byteCount );
                  fileStream->Flush();
                  Console::WriteLine( "Record has been updated." );
               }