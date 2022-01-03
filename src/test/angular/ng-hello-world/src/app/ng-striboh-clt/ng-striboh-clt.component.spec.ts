import { ComponentFixture, TestBed } from '@angular/core/testing';

import { NgStribohCltComponent } from './ng-striboh-clt.component';

describe('HelloComponent', () => {
  let component: NgStribohCltComponent;
  let fixture: ComponentFixture<NgStribohCltComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ NgStribohCltComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(NgStribohCltComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
