--TEST--
Store - SetMulti_PCBC227

--SKIPIF--
<?php
include dirname(__FILE__)."/../../cbtestframework/cbtest-phpt-loader.inc";
couchbase_phpt_skipif("Store", "testSetMulti_PCBC227");

--FILE--
<?php
include dirname(__FILE__)."/../../cbtestframework/cbtest-phpt-loader.inc";
couchbase_phpt_runtest("Store", "testSetMulti_PCBC227");
--EXPECT--
PHP_COUCHBASE_OK