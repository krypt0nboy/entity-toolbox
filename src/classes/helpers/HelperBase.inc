<?php

/**
 * Class HelperBase
 */
class HelperBase {
  use EntityToolboxCommonTraits;

  /**
   * @var object $dataHolder
   *   The object containing the data to help with.
   */
  protected $dataHolder;

  /**
   * @const ALIAS
   */
  const ALIAS = '';

  /**
   * ToolboxPropertiesHelper constructor.
   *
   * @param array $args
   */
  public function __construct(array $args = array()) {
    $this->vedConstructArg($args);
    $this->setUp($args);
  }

  /**
   * Set up function.
   * Sets the helper, and its values.
   *
   * @param array $args
   *   The args to provide for the helper.
   */
  protected function setUp($args = array()) {
    $this->constructSet($args);
  }

  /**
   * Init phase where construct args are set.
   *
   * @param array $args
   */
  protected function constructSet($args) {
    $this->setConstructArgs($args);
    $this->bulkSet($args);
  }

  /**
   * @return object
   */
  public function getDataHolder() {
    return $this->dataHolder;
  }

  /**
   * @param object $dataHolder
   */
  public function setDataHolder($dataHolder) {
    $this->dataHolder = $dataHolder;
  }

  /**
   * Returns the helper data content.
   *
   * @return array
   */
  public function alias() {
    $alias = $this::ALIAS;
    if (!empty($alias)) {
      if (property_exists($this->getDataHolder(), $alias)) {
        return $this->dataHolder->__get($alias);
      }
    }
    else {
      return array();
    }
  }

  /**
   * Returns the number of values for the helper data.
   *
   * @return int
   */
  public function count() {
    return count($this->alias());
  }

}