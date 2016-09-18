<?php

/**
 * Class PropertyCallbacksBuilder
 */
class EntityToolboxInfoPropertyCallbacksBuilder extends EntityToolboxInfoPropertyDependentKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'    => 'callbacks',
        'model_class' => 'EntityToolboxInfoPropertyCallbacksModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  protected function buildGetterCallback() {
    $defaultBuild    = $this->buildKeyDefault('getter');
    $defaultMultiple = $this->getPropertyInstance()->getDefaultMultiple();
    $rawProperty     = $this->getHookBuilder()
                            ->getRawProperties($this->propertyName);
    $rawMultiple     = !empty($rawProperty['multiple']) ? $rawProperty['multiple'] : NULL;
    $multiple        = isset($rawMultiple) ? $rawMultiple : $defaultMultiple;
    if ($multiple) {
      return DEFAULT_MULTI_VALUE_GETTER;
    }
    else {
      return $defaultBuild;
    }
  }

  protected function buildSetterCallback() {
    $defaultBuild    = $this->buildKeyDefault('getter');
    $defaultMultiple = $this->getPropertyInstance()->getDefaultMultiple();
    $rawProperty     = $this->getHookBuilder()
                            ->getRawProperties($this->propertyName);
    $rawMultiple     = !empty($rawProperty['multiple']) ? $rawProperty['multiple'] : NULL;
    $multiple        = isset($rawMultiple) ? $rawMultiple : $defaultMultiple;
    if ($multiple) {
      return DEFAULT_MULTI_VALUE_SETTER;
    }
    else {
      return $defaultBuild;
    }
  }
}