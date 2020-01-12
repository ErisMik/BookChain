import React from "react";
import BlockForm from "./BlockForm";
import logo from "./logo.svg";
import "./App.css";

function App() {
	return (
		<div className="App">
			<header className="App-header">
				<img src={logo} className="App-logo" alt="logo" />
				<BlockForm></BlockForm>
			</header>
		</div>
	);
}

export default App;
