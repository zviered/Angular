import { Component } from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Http} from '@angular/http';
import {IsAliveRequest} from '../icd/PcToTgtIcd';
import {IsAliveReply} from '../icd/PcToTgtIcd';
import {WriteWaveformRequest} from '../icd/PcToTgtIcd';
import {ReadInfoRequest} from '../icd/PcToTgtIcd';
//import {HTTP} from '../services/http/http-service.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})

export class AppComponent {
  title = 'app works!';
  constructor(private http: Http)
  {
    var request = IsAliveRequest;
    var response = IsAliveReply;
    
    console.log ('constructor');

    console.log (ReadInfoRequest);

    var myJSON = JSON.stringify(ReadInfoRequest);
    console.log ('r='+myJSON);
    this.http.post('http://localhost:80',myJSON).subscribe (data => {console.log ('response',data);});
  
  }
}
