using namespace System;
using namespace System::Reflection;
using namespace System::Threading;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Reflection::Emit;
using namespace System::Configuration::Assemblies;
using namespace System::Text;
static void MakeAssembly( AssemblyName^ myAssemblyName, String^ fileName )
{
   // Get the assembly builder from the application domain associated with the current thread.
   AssemblyBuilder^ myAssemblyBuilder = Thread::GetDomain()->DefineDynamicAssembly( myAssemblyName, AssemblyBuilderAccess::RunAndSave );

   // Create a dynamic module in the assembly.
   ModuleBuilder^ myModuleBuilder = myAssemblyBuilder->DefineDynamicModule( "MyModule", fileName );

   // Create a type in the module.
   TypeBuilder^ myTypeBuilder = myModuleBuilder->DefineType( "MyType" );

   // Create a method called 'Main'.
   MethodBuilder^ myMethodBuilder = myTypeBuilder->DefineMethod( "Main", static_cast<MethodAttributes>(MethodAttributes::Public | MethodAttributes::HideBySig | MethodAttributes::Static), void::typeid, nullptr );

   // Get the Intermediate Language generator for the method.
   ILGenerator^ myILGenerator = myMethodBuilder->GetILGenerator();

   // Use the utility method to generate the IL instructions that print a String* to the console.
   myILGenerator->EmitWriteLine( "Hello World!" );

   // Generate the 'ret' IL instruction.
   myILGenerator->Emit( OpCodes::Ret );

   // End the creation of the type.
   myTypeBuilder->CreateType();

   // Set the method with name 'Main' as the entry point in the assembly.
   myAssemblyBuilder->SetEntryPoint( myMethodBuilder );
   myAssemblyBuilder->Save( fileName );
}

int main()
{
   // Create a dynamic assembly with name 'MyAssembly' and build version '1.0.0.2001'.
   AssemblyName^ myAssemblyName = gcnew AssemblyName;

   // Set the codebase to the physical directory were the assembly resides.
   myAssemblyName->CodeBase = Directory::GetCurrentDirectory();

   // Set the culture information of the assembly to 'English-American'.
   myAssemblyName->CultureInfo = gcnew CultureInfo( "en-US" );

   // Set the hash algoritm to 'SHA1'.
   myAssemblyName->HashAlgorithm = AssemblyHashAlgorithm::SHA1;
   myAssemblyName->VersionCompatibility = AssemblyVersionCompatibility::SameProcess;
   myAssemblyName->Flags = AssemblyNameFlags::PublicKey;

   // Provide this assembly with a strong name.
   myAssemblyName->KeyPair = gcnew StrongNameKeyPair( File::Open( "KeyPair.snk", FileMode::Open, FileAccess::Read ) );
   myAssemblyName->Name = "MyAssembly";
   myAssemblyName->Version = gcnew Version( "1.0.0.2001" );
   MakeAssembly( myAssemblyName, "MyAssembly.exe" );

   // Get the assemblies loaded in the current application domain.
   array<Assembly^>^myAssemblies = Thread::GetDomain()->GetAssemblies();

   // Get the dynamic assembly named 'MyAssembly'. 
   Assembly^ myAssembly = nullptr;
   for ( int i = 0; i < myAssemblies->Length; i++ )
      if ( String::Compare( myAssemblies[ i ]->GetName()->Name, "MyAssembly" ) == 0 )
            myAssembly = myAssemblies[ i ];

   // Display the full assembly information to the console.
   if ( myAssembly != nullptr )
   {
      Console::WriteLine( "\nDisplaying the full assembly name.\n" );
      Console::WriteLine( myAssembly->GetName()->FullName );
      Console::WriteLine( "\nDisplaying the public key.\n" );
      array<Byte>^pk;
      pk = myAssembly->GetName()->GetPublicKey();
      for ( int i = 0; i < pk->GetLength( 0 ); i++ )
         Console::Write( " {0:x2}", pk[ i ] );
      Console::WriteLine();
      Console::WriteLine( "\nDisplaying the public key token.\n" );
      array<Byte>^pt;
      pt = myAssembly->GetName()->GetPublicKeyToken();
      for ( int i = 0; i < pt->GetLength( 0 ); i++ )
         Console::Write(  " {0:x2}", pt[ i ] );
   }
}