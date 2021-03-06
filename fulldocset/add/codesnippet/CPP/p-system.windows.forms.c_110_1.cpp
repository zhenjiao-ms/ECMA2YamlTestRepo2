   void BindControls()
   {
      /* Create two Binding objects for the first two TextBox 
            controls. The data-bound property for both controls 
            is the Text property. The data source is a DataSet 
            (ds). The data member is a navigation path in the form: 
            "TableName.ColumnName". */
      text1->DataBindings->Add( gcnew Binding( "Text",ds,"customers.custName" ) );
      text2->DataBindings->Add( gcnew Binding( "Text",ds,"customers.custID" ) );

      /* Bind the DateTimePicker control by adding a new Binding. 
            The data member of the DateTimePicker is a navigation path:
            TableName.RelationName.ColumnName string. */
      DateTimePicker1->DataBindings->Add( gcnew Binding( "Value",ds,"customers.CustToOrders.OrderDate" ) );

      /* Add event delegates for the Parse and Format events to a 
            new Binding object, and add the object to the third 
            TextBox control's BindingsCollection. The delegates 
            must be added before adding the Binding to the 
            collection; otherwise, no formatting occurs until 
            the Current object of the BindingManagerBase for 
            the data source changes. */
      Binding^ b = gcnew Binding( "Text",ds,"customers.custToOrders.OrderAmount" );
      b->Parse += gcnew ConvertEventHandler( this, &Form1::CurrencyStringToDecimal );
      b->Format += gcnew ConvertEventHandler( this, &Form1::DecimalToCurrencyString );
      text3->DataBindings->Add( b );

      // Get the BindingManagerBase for the Customers table. 
      bmCustomers = this->BindingContext[ ds,"Customers" ];

      /* Get the BindingManagerBase for the Orders table using the 
            RelationName. */
      bmOrders = this->BindingContext[ds, "customers.CustToOrders"];

      /* Bind the fourth TextBox control's Text property to the
         third control's Text property. */
      text4->DataBindings->Add( "Text", text3, "Text" );
   }