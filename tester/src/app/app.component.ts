import { Component, Input } from '@angular/core';
import { ToolbarComponent} from 'src/app/component/toolbar/toolbar.component';
import { MainComponent} from 'src/app/component/main/main.component';
import { DataService} from 'src/app/service/data.service'
import { SysconfigService} from './service/sysconfig.service'

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],

})
export class AppComponent {
   toolBarComponent : ToolbarComponent;
   mainComponent : MainComponent;


  constructor(svc: DataService, cfg: SysconfigService) {
    console.log ('constructor AppComponent');
   }
  title = 'Tester';

}
