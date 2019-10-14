import { Component, Input } from '@angular/core';
import { ToolbarComponent} from 'src/app/component/toolbar/toolbar.component';
import { MainComponent} from 'src/app/component/main/main.component';
import { DataService} from './data.service'

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],

})
export class AppComponent {
   toolBarComponent : ToolbarComponent;
   mainComponent : MainComponent;


  constructor(svc: DataService) {
    console.log ('constructor AppComponent');
   }
  title = 'Tester';

}
