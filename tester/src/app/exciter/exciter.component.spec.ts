import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ExciterComponent } from './exciter.component';

describe('ExciterComponent', () => {
  let component: ExciterComponent;
  let fixture: ComponentFixture<ExciterComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ExciterComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ExciterComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
