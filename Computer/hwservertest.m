javaclasspath('C:\Users\Bobby Cohen\Documents\MATLAB\surefirebooter8729299268307298583.jar');
import org.zeromq.ZMQ;

ctx = zmq.Ctx();

socket = ctx.createSocket(ZMQ.REP);

socket.bind('tcp://192.168.99.1:7575');

message = socket.recv(0);
json_data = native2unicode(message.data)';

message = zmq.Msg(8);
message.put(unicode2native('Received'));
socket.send(message, 0);

socket.close();