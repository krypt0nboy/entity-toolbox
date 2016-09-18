<?php

/**
 * Class EntityToolboxCommonTraits
 */
trait EntityToolboxCommonTraits {
  /**
   * @var array $constructArgs
   */
  protected $constructArgs = array();

  /**
   * Getter.
   *
   * @param string $name
   *   The property name.
   *
   * @return mixed
   */
  public function __get($name) {
    $method = 'get' . lowercase2camelcase($name);
    if (method_exists($this, $method)) {
      return $this->$method();
    }
  }

  /**
   * Setter.
   *
   * @param string $name
   *   The property name.
   *
   * @param mixed  $value
   *   The value to set.
   */
  public function __set($name, $value) {
    $cKey   = lowercase2camelcase($name);
    $method = 'set' . $cKey;
    if (method_exists($this, $method)) {
      $this->preSet($name);
      $this->$method($value);
      $this->postSet($cKey, $value);
    }
  }

  /**
   * Sets an array of args.
   *
   * @param array $args
   *   The args to set.
   */
  public function bulkSet(array $args = array()) {
    foreach ($args as $argName => $arg) {
      $this->__set($argName, $arg);
    }
  }

  /**
   * Check if a property is set.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function __isset($name) {
    $cKey = lcfirst(lowercase2camelcase($name));

    return isset($this->{$cKey}) && !empty($this->{$cKey});
  }

  /**
   * @param $name
   */
  protected function preSet($name) {
    $cKey   = lowercase2camelcase($name);
    $method = "preSet$cKey";
    if (method_exists($this, $method)) {
      $this->$method();
    }
  }

  /**
   * @param $name
   * @param $value
   */
  protected function postSet($name, $value) {
    $method = "postSet$name";
    if (method_exists($this, $method)) {
      $this->$method($value);
    }
  }

  /**
   * @param array $args1
   * @param array $args2
   * @return array
   */
  protected function mergeConstructArgs(array $args1 = array(), array $args2 = array()) {
    $merged = array_replace_recursive($args1, $args2);

    return $merged;
  }

  /**
   * @return array
   */
  public function getConstructArgs() {
    return $this->constructArgs;
  }

  /**
   * @param array $constructArgs
   */
  public function setConstructArgs($constructArgs) {
    $this->constructArgs = $constructArgs;
  }

  /**
   * Checks that every required arg is provided.
   *
   * @param array $args
   *   The construct args to check.
   */
  protected function vedConstructArg(array $args = array()) {
  }

}