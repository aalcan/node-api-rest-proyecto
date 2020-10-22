// Cargamos el modelo recien creado
const interruptorModel = require('../models/interruptores');

// Codificamos las operaciones que se podran realizar con relacion a los usuarios
module.exports = {
// Metodo para la busqueda de interruptores por ID
 getById: async (req, res, next) =>{
  console.log(req.body);
  interruptorModel.findById(req.params.interruptorId, function(err, interruptorInfo){
   if (err) {
    next(err);
   } else {
    res.json({status:"success", message: "Interruptor found!!!", data:{interruptor: interruptorInfo}});
   }
  });
 },
//Metodo para retornar todos los interruptores registrados en la base de datos
getAll: async (req, res, next)  => {
  let interruptores = [];
  await interruptorModel.find({}, function(err, Interruptores){
  	if (err){
  		next(err);
  	} else{
  		for (let interruptor of Interruptores) {
  			interruptores.push({id: interruptor._id, nombre: interruptor.nombre, estado: interruptor.estado});
  		}
  		res.json({status:"success", message: "Interruptores list found!!!", data:{Interruptores: interruptores}}); 
  	}
   });
},

//Metodo para crear algun registro nuevo
create: async(req, res, next) => {
  await interruptorModel.create(req.body, function (err, result) {
      if (err) 
       next(err);
      else
       res.json({status: "success", message: "Interruptor added successfully!!!", data: req.body});
      
    });
 },
}
