import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'app works!';
  constructor()
  {
    //alert("Hello");
    setInterval (function(){ 
      console.log ('Timer'); 
    }, 1000);
  }
}
