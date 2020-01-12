import React from "react";

class BlockForm extends React.Component {
	constructor(props) {
		super(props);
		this.state = {
			value: "",
			viewUncompressed: false,
			blockHeight: null,
			blockData: null,
			uncompressedBlockData: "",
			blockHash: null,
			prevHash: null,
			nonce: null
		};

		this.updateBlock = this.updateBlock.bind(this);
		this.updateData = this.updateData.bind(this);
		this.handleCompressedInput = this.handleCompressedInput.bind(this);
	}

	componentDidUpdate(prevProps, prevState) {
		if (this.state.blockHeight !== prevState.blockHeight) {
			this.updateData();
		}
	}

	updateBlock(event) {
		const eventVal = event.target.value;

		const blockUrl = "http://localhost:5000/get-block/" + eventVal;
		fetch(blockUrl)
			.then(res => res.json())
			.then(json => {
				this.setState({
					value: eventVal,
					blockHeight: json.height,
					blockData: json.data,
					blockHash: json.hash,
					prevHash: json.prevhash,
					nonce: json.nonce
				});
			})
	}

	updateData() {
		if (!this.state.value) {
			return
		}

		if (this.state.viewUncompressed) {
			const bookUrl = "http://localhost:5000/get-book/" + this.state.value;
			fetch(bookUrl)
				.then(res => res.json())
				.then(json => {
					this.setState({
						uncompressedBlockData: json.text
					});
				})
		}
	}

	handleCompressedInput(event) {
		console.log(event.target.checked)
		this.setState({viewUncompressed: event.target.checked});
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
					<br/>
					<label>
						Uncompress?:
						<input
							type="checkbox"
							// value={this.state.viewUncompressed}
							onChange={this.handleCompressedInput}
						/>
					</label>
				</form>
				<p>Block Height: {this.state.blockHeight}</p>
				<p>Hash: {this.state.blockHash}</p>
				<p>Previous Hash: {this.state.prevHash}</p>
				<p>Nonce: {this.state.nonce}</p>
				{
					this.state.viewUncompressed
					?
						<pre>Text: {this.state.uncompressedBlockData}</pre>
					:
						<p>Data: {this.state.blockData}</p>
				}
			</div>
		);
	}
}

export default BlockForm;
