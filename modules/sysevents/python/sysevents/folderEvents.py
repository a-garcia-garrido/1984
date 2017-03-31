import pyinotify

class MyEventHandeler(pyinotify.ProcessEvent):
    def process_IN_ACCESS(self, event):
        print "ACCESS event: ", event.pathname
    def process_IN_CREATE(self, event):
        print event.path
        print event.name

def main():
    wm = pyinotify.WatchManager()
    wm.add_watch('/home/dam/prueba', pyinotify.ALL_EVENTS, rec=True)

    eh = MyEventHandeler()

    notifier = pyinotify.Notifier(wm, eh)
    notifier.loop()

if __name__ == '__main__':
    main()
