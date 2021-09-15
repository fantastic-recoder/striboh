import { ComponentFixture, TestBed } from '@angular/core/testing';

import { NgStribohComponent } from './ng-striboh.component';

describe('NgStribohComponent', () => {
  let component: NgStribohComponent;
  let fixture: ComponentFixture<NgStribohComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ NgStribohComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(NgStribohComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
