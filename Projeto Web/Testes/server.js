const express = require('express');
const { Pool } = require('pg');
const cors = require('cors');

const app = express();
const PORT = 3001;

// Configuração do PostgreSQL
const pool = new Pool({
    user: 'postgres', 
    host: 'localhost',
    database: 'meu_banco',
    password: 'SenhaPostgres@2024!',  // Substitua pela senha correta do PostgreSQL
    port: 5432,
});

// Middlewares
app.use(express.json());
app.use(cors());

// Rota para cadastrar usuário
app.post('/cadastrar', async (req, res) => {
    const { nome, email, senha } = req.body;
    try {
        await pool.query(
            'INSERT INTO usuarios (nome, email, senha) VALUES ($1, $2, $3)',
            [nome, email, senha]
        );
        res.json({ message: 'Usuário cadastrado com sucesso!' });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

// Iniciar o servidor
app.listen(PORT, () => {
    console.log(`Servidor rodando na porta ${PORT}`);
});
