async function loadBlockchain() {
    try {
        const res = await fetch('../blockchain.json');
        const chain = await res.json();

        const container = document.getElementById('blocks');
        container.innerHTML = '';

        chain.forEach(block => {
            const div = document.createElement('div');
            div.className = 'block';
            div.innerHTML = `
                <b>Index:</b> ${block.index}<br>
                <b>Data:</b> ${block.data}<br>
                <b>Hash:</b> <code>${block.hash}</code><br>
                <b>Previous Hash:</b> <code>${block.previousHash}</code>
            `;
            container.appendChild(div);
        });
    } catch (err) {
        console.error("Failed to load blockchain.json", err);
    }
}

loadBlockchain();
