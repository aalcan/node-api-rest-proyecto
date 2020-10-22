// Cargamos el modelo recien creado
const interruptorModel = require('../models/interruptores');

// Codificamos las operaciones que se podran realizar con relacion a los usuarios
module.exports = {
// Metodo para la busqueda de videojuegos por ID
 getById: function(req, res, next) {
  console.log(req.body);
  interruptorModel.findById(req.params.interruptorId, function(err, interruptorInfo){
   if (err) {
    next(err);
   } else {
    res.json({status:"success", message: "Interruptor found!!!", data:{interruptor: interruptorInfo}});
   }
  });
 },
//Metodo para retornar todos los videojuegos registrados en la base de datos
getAll: function(req, res, next) {
  let interruptores = [];
  interruptorModel.find({}, function(err, Interruptores){
  	if (err){
  		next(err);
  	} else{
  		for (let interruptor of Interruptores) {
  			interruptores.push({id: interruptor._id, nombre: interruptor.nombre, estado: interruptor.esta commdo});
  		}
  		res.json({status:"success", message: "Interruptores list found!!!", data:{Interruptores: interruptores}}); 
  	}
   });
},

//Metodo para crear algun registro nuevo
create: function(req, res, next) {
  interruptorModel.create(req.body, function (err, result) {
      if (err) 
       next(err);
      else
       res.json({status: "success", message: "Interruptor added successfully!!!", data: req.body});
      
    });
 },
}
