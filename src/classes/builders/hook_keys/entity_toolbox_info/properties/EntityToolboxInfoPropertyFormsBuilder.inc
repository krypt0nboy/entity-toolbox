<?php

/**
 * Class PropertyFormsBuilder
 */
class EntityToolboxInfoPropertyFormsBuilder extends EntityToolboxInfoPropertyDependentKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'    => 'forms',
        'model_class' => 'EntityToolboxInfoPropertyFormsModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  protected function postSetPropertyInstance() {
    parent::postSetPropertyInstance();
    $keyBuilders = array();
    foreach ($this->getStructure() as $formType => $structureKey) {
      $keyBuilders[$formType] = $this->keyBuilderGetInstance('EntityToolboxInfoPropertyFormBuilder', array(
        'form_type' => $formType
      ));
    }
    $this->setKeyBuilders($keyBuilders);
  }

  protected function buildPropertyEditForm() {
    return $this->getKeyBuilder('edit')->build();
  }
}