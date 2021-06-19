const express = require('express');
const routes = express.Router();
const ProductController = require('./controllers/Controller');
routes.post('/:value', ProductController.enviar);
routes.get('/', ProductController.buscar);
module.exports = routes;
