import { Http } from '@angular/http';
import 'rxjs/add/operator/map';
import {HttpClient} from '@angular/common/http';

type PERSON = { firstName: string, lastName: string };

export class AppClass {

  private mPerson: PERSON;

  constructor (private http: HttpClient) {
  }
  public openFile (file) {
      let name = '';

      /*this.http.get('http://api.icndb.com/jokes/random').subscribe(data => {
        name = data['value'];*/

        this.http.get('/api/person.json').subscribe(data => {
          name = data['firstName'];

      console.log (name);
    });
  };

};
