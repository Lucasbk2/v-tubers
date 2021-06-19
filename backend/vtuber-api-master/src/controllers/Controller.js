let value = { message: 0 }
module.exports = {
    async buscar(req, res) {
        return res.json(value);
    },
    async enviar(req, res) {
        value = { message: req.params.value }
        return res.json(value);
    }
};
