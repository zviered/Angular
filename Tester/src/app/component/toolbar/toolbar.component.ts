import { Component, OnInit } from '@angular/core';
import {HttpClient, HttpHeaders, HttpHeaderResponse} from '@angular/common/http';
import {DataService} from '../../data.service'

@Component({
  selector: 'app-toolbar',
  templateUrl: './toolbar.component.html',
  styleUrls: ['./toolbar.component.scss']
})
export class ToolbarComponent implements OnInit {

  constructor(private http: HttpClient, private svc: DataService) { 
    console.log ('constructor ToolbarComponent');
    
  }

  /********************************************************************/
  public onOpenFile (event)
  {
    var xmlDoc;
    var parser;
    var text = "<bookstore><book>" +
                "<title>Everyday Italian</title>" +
                "<author>Giada De Laurentiis</author>" +
                "<year>2005</year>" +
                "</book></bookstore>";

    var textJson = '{ "employees" : [' +
    '{ "firstName":"John" , "lastName":"Doe" },' +
    '{ "firstName":"Anna" , "lastName":"Smith" },' +
    '{ "firstName":"Peter" , "lastName":"Jones" } ]}';

    parser = new DOMParser();
    xmlDoc = parser.parseFromString(text,"text/xml");
    console.log('xmldoc');
    console.log(xmlDoc);

    console.log('jsonDoc');
    var jsonDoc = JSON.parse(textJson);
    console.log (jsonDoc);

    this.http.get ('http://localhost:80/api/dwell.xml',{ responseType: 'text' }).subscribe(
      (val) => {
          console.log("GET call successful value returned in body", 
                      val);
      },
      response => {
          console.log("GET call in error", response);
      },
      () => {
          console.log("The GET observable is now completed.");
      });  
      
      console.log (this.svc._fullName);
  }

  ngOnInit() {
  }

}
