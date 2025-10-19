async function loadBlockchain() {
    const res = await fetch('blockchain.json');
    const blockchain = await res.json();

    const container = document.getElementById('chain');
    container.innerHTML = '';

    const keys = Object.keys(blockchain);
    keys.forEach((key, idx) => {
        const block = blockchain[key];

        const blockDiv = document.createElement('div');
        blockDiv.className = 'block';
        blockDiv.innerHTML = `
            <b>Index:</b> ${block.index}<br>
            <b>Data:</b> ${block.data}<br>
            <b>Hash:</b> <code>${block.hash}</code><br>
            <b>PrevHash:</b> <code>${block.previousHash}</code>
        `;
        container.appendChild(blockDiv);

        // Only add arrow if next block exists on the same row
        if (idx < keys.length - 1) {
            const arrowDiv = document.createElement('div');
            arrowDiv.className = 'arrow';
            container.appendChild(arrowDiv);
        }
    });
}

loadBlockchain();
