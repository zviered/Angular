import { Component } from '@angular/core';
import { Model, TodoItem } from './model';
@Component({
  selector: 'app-root',
  templateUrl: 'app.component.html'
})
export class AppComponent {
  selectedMode : string;
  saveUsername : boolean;
  model : Model;

  constructor() {
    this.saveUsername = true;
    this.selectedMode = 'Tracking';
    this.model = new Model();
    console.log (this.selectedMode);
  }

  getName() {
    return this.model.user;
  }
  getTodoItems() {
    return this.model.items;
  }

  getBypass () {
    return this.saveUsername;
  }
  addItem(newItem) {
    if (newItem !== '') {
      this.model.items.push(new TodoItem(newItem, false));
    }
  }
}
