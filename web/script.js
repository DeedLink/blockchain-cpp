async function loadBlockchain() {
    const container = document.getElementById('chain');
    
    try {
        const res = await fetch('blockchain.json');
        const blockchain = await res.json();

        container.innerHTML = '';

        Object.values(blockchain).forEach(block => {
            const blockDiv = document.createElement('div');
            blockDiv.className = 'block';
            blockDiv.innerHTML = `
                <div class="block-header">
                    <div class="block-index">BLOCK #${block.index}</div>
                    <div class="block-icon">⛓️</div>
                </div>
                <div class="block-content">
                    <div class="block-field">
                        <div class="block-label">Data</div>
                        <div class="block-value">${block.data}</div>
                    </div>
                    <div class="block-field">
                        <div class="block-label">Hash</div>
                        <div class="block-hash">${block.hash}</div>
                    </div>
                    <div class="block-field">
                        <div class="block-label">Previous Hash</div>
                        <div class="block-hash prev-hash">${block.previousHash}</div>
                    </div>
                </div>
            `;
            container.appendChild(blockDiv);
        });
    } catch (error) {
        container.innerHTML = '<div class="loading">Error loading blockchain.json</div>';
        console.error('Error loading blockchain:', error);
    }
}

loadBlockchain();