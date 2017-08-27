import { Component } from '@angular/core';
import {
  Router
} from '@angular/router';
import {AppClass} from './app.class';
import {HttpClient} from '@angular/common/http';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})

export class AppComponent {

  app: AppClass;

  constructor(private http: HttpClient) {

    const file = './person.json';
    this.app = new AppClass(http);

    this.app.openFile(file);

    /*if (router!=null)
      console.log (router);*/
    console.log ('constructor');

  };

  openFile() {
    console.log ('openFile');
    /*this.app.openFile('person.json');*/
  }
}
