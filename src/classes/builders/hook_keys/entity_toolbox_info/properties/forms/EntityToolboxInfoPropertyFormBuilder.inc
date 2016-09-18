<?php

/**
 * Class EntityToolboxInfoPropertyFormBuilder
 */
class EntityToolboxInfoPropertyFormBuilder extends EntityToolboxInfoPropertyDependentKeyBuilder {
  /**
   * @var string $formType
   */
  protected $formType;

  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityToolboxInfoPropertyFormsFormModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * @return mixed
   */
  public function getFormType() {
    return $this->formType;
  }

  /**
   * @param mixed $formType
   */
  public function setFormType($formType) {
    $this->formType = $formType;
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += array('form_type', $this->formType);
    parent::initTemplateVars($vars);
  }
}