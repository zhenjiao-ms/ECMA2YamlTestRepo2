private void DecimalToCurrencyString(object sender, ConvertEventArgs cevent)
{
   // The method converts only to string type. Test this using the DesiredType.
   if(cevent.DesiredType != typeof(string)) return;

   // Use the ToString method to format the value as currency ("c").
   cevent.Value = ((decimal) cevent.Value).ToString("c");
}

private void CurrencyStringToDecimal(object sender, ConvertEventArgs cevent)
{
   // The method converts back to decimal type only. 
   if(cevent.DesiredType != typeof(decimal)) return;

   // Converts the string back to decimal using the static Parse method.
   cevent.Value = Decimal.Parse(cevent.Value.ToString(),
   NumberStyles.Currency, null);
}

private void BindControl()
{
   // Creates the binding first. The OrderAmount is a Decimal type.
   Binding b = new Binding
      ("Text", ds, "customers.custToOrders.OrderAmount");
   // Add the delegates to the event.
   b.Format += new ConvertEventHandler(DecimalToCurrencyString);
   b.Parse += new ConvertEventHandler(CurrencyStringToDecimal);
   text1.DataBindings.Add(b);
}
