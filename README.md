# ext/couchbase

A PHP extension wrapping libcouchbase.

## Dependencies

libcouchbase

## Installation

    $ phpize
    $ ./configure
    $ make
    $ make test
    $ make install

Running make test assumes that you have a Couchbase server listening
on port 127.0.0.1:8091

If you are using a webserver installation of PHP, you might need to
restart your webserver.

## First Step

Create a new script `test.php`:

    <?php
    $cb = new Couchbase("127.0.0.1:8091", "Administrator",
                        "password", "default");
    $cb->set("a", 1);
    $a = $cb->get("a");
    echo $a;
    ?>

# Compatibility

PHP 5.2.9 or later.

Windows support is coming in the next release.

## License

Apache License 2.0

## Credits

See CREDITS file. Thanks all!

## Copyright

(c) 2011, 2012 Couchbase
