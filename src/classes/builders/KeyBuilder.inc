<?php

/**
 * Class KeyBuilder
 */
class KeyBuilder extends BuilderBase {
  /**
   * @var BuilderBase $parentBuilder
   *   The parent builder.
   */
  protected $parentBuilder;
  /**
   * @var string $selfKey
   */
  protected $selfKey;
  /**
   * @var string $parentKey
   */
  protected $parentKey;
  /**
   * @var boolean $requiresRebuild
   */
  protected $requiresRebuild;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
  }

  /**
   * @return BuilderBase
   */
  public function getParentBuilder() {
    return $this->parentBuilder;
  }

  /**
   * @param BuilderBase $parentBuilder
   */
  public function setParentBuilder($parentBuilder) {
    $this->parentBuilder = $parentBuilder;
  }

  /**
   * @return string
   */
  public function getSelfKey() {
    return $this->selfKey;
  }

  /**
   * @param string $selfKey
   */
  public function setSelfKey($selfKey) {
    $this->selfKey = $selfKey;
  }

  /**
   * @return string
   */
  public function getParentKey() {
    return $this->parentKey;
  }

  /**
   * @param string $parentKey
   */
  public function setParentKey($parentKey) {
    $this->parentKey = $parentKey;
  }

  /**
   * @return boolean
   */
  public function getRequiresRebuild() {
    return $this->requiresRebuild;
  }

  /**
   * @param boolean $requiresRebuild
   */
  public function setRequiresRebuild($requiresRebuild) {
    $this->requiresRebuild = $requiresRebuild;
  }

  /**
   * @param       $keyBuilderClass
   * @param array $args
   *
   * @return mixed
   */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'parent_builder' => $this,
      'parent_key'     => $this->getSelfKey(),
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }

  /**
   * @param null $key
   * @return array
   */
  public function getTemplateVars($key = NULL) {
    $selfVars    = $this->templateVars;
    $parentVars  = $this->getParentBuilder()->getTemplateVars();
    $updatedVars = $selfVars + $parentVars;

    return isset($key) ? $updatedVars[$key] : $updatedVars;
  }

  /**
   * @param array $vars
   */
  protected function updateParentBuilderTemplateVars(array $vars = array()) {
    foreach ($vars as $var => $value) {
      $this->getParentBuilder()->updateTemplateVar($var, $value);
    }
  }

  /** {{@inheritdoc}} */
  protected function postBuild() {
  }
}