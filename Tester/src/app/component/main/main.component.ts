import { Component, OnInit} from '@angular/core';
import {HttpClient} from '@angular/common/http';

@Component({
  selector: 'app-main',
  templateUrl: './main.component.html',
  styleUrls: ['./main.component.scss']
})

export class MainComponent implements OnInit {

  /********************************************************************/
  constructor(private http: HttpClient) 
  { 
    console.log ('constructor MainComponent');
    
  }

  /********************************************************************/
  ngOnInit() {
  }

}
