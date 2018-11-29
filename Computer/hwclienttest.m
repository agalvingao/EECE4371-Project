javaclasspath('C:\Users\Bobby Cohen\Documents\MATLAB\surefirebooter8729299268307298583.jar');
import org.zeromq.ZMQ;

ctx = zmq.Ctx();

socket = ctx.createSocket(ZMQ.REQ);

socket.connect('tcp://192.168.99.1:7575');

message = zmq.Msg(8);
message.put(unicode2native('Received'));
socket.send(message, 0);

message = socket.recv(0);
json_data = native2unicode(message.data)';
disp(message);