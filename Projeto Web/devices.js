// Função para cadastrar Dispositivo
async function cadastrarUsuario() {
    const devicename = document.getElementById('devicename').value;
    const id = document.getElementById('id').value;
    const password = document.getElementById('password').value;

    try {
        const response = await fetch('http://localhost:3001/cadastrar-usuario', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ devicename, id, password })
        });

        const result = await response.json();
        alert(result.message);
        limparFormulario();
    } catch (error) {
        alert('Erro ao cadastrar usuário: ' + error.message);
        limparFormulario();
    }    

}

function toggleTabContent(index) {
    const tabContents = document.querySelectorAll('.tab-content');
    const arrows = document.querySelectorAll('.tab i');
    
    // Fecha todos os conteúdos abertos e reseta a flexinha
    tabContents.forEach((content, idx) => {
        if (idx === index) {
            content.classList.toggle('active'); // Mostra ou esconde o conteúdo
        } else {
            content.classList.remove('active'); // Fecha outros
        }
    });
    
    // Ajusta o ícone de flexinha
    arrows.forEach((arrow, idx) => {
        if (idx === index) {
            arrow.classList.toggle('rotate'); // Gira a flexinha
        } else {
            arrow.classList.remove('rotate'); // Reseta a flexinha de outros
        }
    });
}