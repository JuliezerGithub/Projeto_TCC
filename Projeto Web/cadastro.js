        // Função para alternar entre as abas
        function openTab(tabId) {
            var contents = document.getElementsByClassName('tab-content');
            for (var i = 0; i < contents.length; i++) {
                contents[i].classList.remove('tab-active');
            }
            document.getElementById(tabId).classList.add('tab-active');
        }

        // Funções para enviar os dados do formulário
        function cadastrarUsuario() {
            const username = document.getElementById('username').value;
            const email = document.getElementById('email').value;
            const password = document.getElementById('password').value;
            
            // Envia os dados ao backend via POST (fetch ou XMLHttpRequest)
            fetch('/cadastrar-usuario', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ username, email, password })
            }).then(response => response.json())
              .then(data => alert('Usuário cadastrado com sucesso!'))
              .catch(error => console.error('Erro:', error));
        }

        function consultarUsuario() {
            const username = document.getElementById('consultaUsername').value;
            
            fetch(`/consultar-usuario?username=${username}`)
            .then(response => response.json())
            .then(data => {
                document.getElementById('resultadoConsulta').innerHTML = JSON.stringify(data);
            })
            .catch(error => console.error('Erro:', error));
        }

        function excluirUsuario() {
            const username = document.getElementById('exclusaoUsername').value;
            
            fetch(`/excluir-usuario`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ username })
            }).then(response => response.json())
              .then(data => alert('Usuário excluído com sucesso!'))
              .catch(error => console.error('Erro:', error));
        }

        function alterarPerfil() {
            const username = document.getElementById('perfilUsername').value;
            const novoPerfil = document.getElementById('novoPerfil').value;
            
            fetch(`/alterar-perfil`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ username, novoPerfil })
            }).then(response => response.json())
              .then(data => alert('Perfil alterado com sucesso!'))
              .catch(error => console.error('Erro:', error));
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