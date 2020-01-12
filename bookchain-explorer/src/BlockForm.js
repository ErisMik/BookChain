import React from "react";

class BlockForm extends React.Component {
	constructor(props) {
		super(props);
		this.state = {
			value: "200",
			blockHeight: null,
			blockData: null,
			blockHash: null,
			prevHash: null,
			nonce: null
		};

		this.handleSubmit = this.handleSubmit.bind(this);
		this.updateBlock = this.updateBlock.bind(this);
	}

	updateBlock(event) {
		this.setState({ value: event.target.value });
	}

	handleSubmit(event) {
		console.log(event);
		//Grab the block data
		const blockUrl = "http://localhost:5000/get-block/" + this.state.value;
		fetch(blockUrl)
			.then(res => res.json())
			.then(json => {
				this.setState({
					blockHeight: json.height,
					blockData: json.data,
					blockHash: json.hash,
					prevHash: json.prevhash,
					nonce: json.nonce
				});
			});
	}

	render() {
		if (this.state.blockHeight === null) {
			return (
				<form>
					<label>
						Block Number:
						<input
							type="text"
							value={this.state.value}
							onChange={this.updateBlock}
						/>
					</label>
					<input type="submit" value="Go!" onClick={this.handleSubmit} />
				</form>
			);
		}
		return (
			<div>
				<form>
					<label>
						Block Number:
						<input
							type="text"
							value={this.state.value}
							onChange={this.updateBlock}
						/>
					</label>
					<input type="submit" value="Go!" onClick={this.handleSubmit} />
				</form>
				<p>Block Height: {this.state.blockHeight}</p>
				<p>Hash: {this.state.blockHash}</p>
				<p>Previous Hash: {this.state.prevHash}</p>
				<p>Data: {this.state.blockData}</p>
				<p>Nonce: {this.state.nonce}</p>
			</div>
		);
	}
}

export default BlockForm;
