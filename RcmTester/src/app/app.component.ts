import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'app works!';
  private readData : string;

  constructor ()
  {
    this.readData = "";
  }
  writeWord (deviceId, offset, data)
  {
    console.log ("write to device["+deviceId+"] offset="+offset+" data="+data);
  }

  readWord (deviceId, offset)
  {
    console.log ("read from device["+deviceId+"] offset="+offset+" data=?");
    this.readData = "0x20";
  }
}
