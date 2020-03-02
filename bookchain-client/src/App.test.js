import React from 'react';
import { mount, shallow } from 'enzyme';
import App from './App';
import ApplicationBar from './components/ApplicationBar'

test('renders ApplicationBar', () => {
  const app = mount(<App />);

  expect(app.contains(ApplicationBar)).toEqual(true);
});

test('renders Home by default', () => {
  const app = mount(<App />);

  expect(app.exists("#home")).toEqual(true);
});
