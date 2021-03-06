     // Create a Port.
     Port postPort = new Port();
     postPort.Name = "PortServiceHttpPost";
     postPort.Binding = new XmlQualifiedName("s0:PortServiceHttpPost");

     // Create an HttpAddressBinding.
     HttpAddressBinding postAddressBinding = new HttpAddressBinding();
     postAddressBinding.Location = 
        "http://localhost/PortClass/PortService_cs.asmx";

     // Add the HttpAddressBinding to the Port.
     postPort.Extensions.Add(postAddressBinding);

     // Get the Service of the postPort.
     Service myService = postPort.Service;

     // Print the service name for the port.
     Console.WriteLine("This is the service name of the postPort:*" +
        myDescription.Services[0].Ports[0].Service.Name + "*");

     // Add the Port to the PortCollection of the ServiceDescription.
     myDescription.Services[0].Ports.Add(postPort);