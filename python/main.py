import subprocess

import cherrypy

# open the process
class HelloWorld(object):
	def index(self):

		# should use argument instead
		subprocess.Popen(["/home/asdf/audioBuild/./AudioMain"])
		return "completed!"
	index.exposed = True

cherrypy.quickstart(HelloWorld())