<?php

/**
 * Class KeyBuilder
 */
class KeyBuilder extends BuilderBase {
  /**
   * @var BuilderBase $parentBuilder
   */
  protected $parentBuilder;
  /**
   * @var string $selfKey
   */
  protected $selfKey;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $build = parent::build();
    $this->updateParentBuilderTemplateVars();

    return $build;
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
   * @param       $keyBuilderClass
   * @param array $args
   *
   * @return mixed
   */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'parent_builder' => $this,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }

  /**
   * @param $value
   * @return string
   */
  protected function processValueTemplate($value) {
    return $this->isValueTemplate($value) ? string_template_process($value, $this->getUpdatedTemplateVars()) : $value;
  }

  /**
   *
   */
  protected function initTemplateVars() {
    $vars = $this->getUpdatedTemplateVars();
    $this->setTemplateVars($vars);
  }

  /**
   * @param array $vars
   */
  protected function updateParentBuilderTemplateVars(array $vars = array()) {
    foreach ($vars as $var => $value) {
      $this->getParentBuilder()->updateTemplateVars($var, $value);
    }
  }

  /**
   *
   */
  public function getUpdatedTemplateVars() {
    $selfTemplateVars          = array();
    $parentBuilderTemplateVars = $this->getParentBuilder()->getTemplateVars();
    $vars                      = $selfTemplateVars + $parentBuilderTemplateVars;

    return $vars;
  }
}